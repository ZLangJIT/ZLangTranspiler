#ifndef ZLANG_MICROCPU2_H
#define ZLANG_MICROCPU2_H

#include <memory>
#include <functional>
#include <queue>
#include <deque>
#include <stdexcept>

enum MICROCPU2_OP {
    MICROCPU2_OP_NOP,
    MICROCPU2_OP_EXE,
    MICROCPU2_OP_JUMP_DOWN_RELATIVE,
    MICROCPU2_OP_JUMP_UP_RELATIVE,
    MICROCPU2_OP_JUMP_ABSOLUTE,
    MICROCPU2_OP_CONDITIONAL_JUMP_DOWN_RELATIVE,
    MICROCPU2_OP_CONDITIONAL_JUMP_UP_RELATIVE,
    MICROCPU2_OP_CONDITIONAL_JUMP_ABSOLUTE,
    MICROCPU2_OP_PUSH_POP_CONTEXT,
    MICROCPU2_OP_PUSH_POP_INSTRUCTION_LIST,
};

// https://github.com/royvandam/rtti

struct MicroCpu2 final {

    struct Context {

        // static cast object to   [ void* ]  and then static cast it to your desired subclass
        //
        // this avoids "object slicing" due to
        //
        // "Things like padding compression or virtual functions or even `[[no_unique_address]]` or stuff can all (as far as I'm aware) result in the base and derived class objects no longer being pointer-interconvertible"
        //
        // and
        //
        // "Note that the address of a base class subobject is not necessarily the same as the address of the complete derived class object, there can be adjustments required if not standard-layout"
        //
        //
        void * user_data;
        std::function<void(void*)> deleter;
        
        inline Context() : user_data(nullptr), deleter([](void*p){}) {}
        inline Context(void * user_data) : user_data(user_data), deleter([](void*p){}) {}
        inline Context(void * user_data, std::function<void(void*)> deleter) : user_data(user_data), deleter(deleter) {}
        virtual inline ~Context() { deleter(user_data); }
    };
    
    public:
    
    inline MicroCpu2() {}

    struct InstructionList {
        private:

        friend MicroCpu2;

        struct OP_NOP {
            MICROCPU2_OP op;
            inline OP_NOP() { op = MICROCPU2_OP_NOP; }
            inline virtual void print() { printf("NOP\n"); }
            inline virtual void exe(MicroCpu2 * cpu) {}
            inline virtual ~OP_NOP() {}
        };
        
        struct OP_EXE : OP_NOP {
            std::function<void(void*)> f;
            inline OP_EXE(const std::function<void(void*)> & f) : f(f) { this->op = MICROCPU2_OP_EXE; };
            inline void print() override { f.target<void(*)(void*)>() == nullptr ? printf("CALL <0x0 or lambda>\n") : printf("CALL %p\n", f.target<void(*)(void*)>()); }
            inline void exe(MicroCpu2 * cpu) override {
                f.operator()(cpu->current_context->user_data);
            }
        };
        
        struct OP_JUMP : OP_NOP {
            size_t jump_position;
            inline OP_JUMP(size_t jump_position) : jump_position(jump_position) {
                this->op = MICROCPU2_OP_JUMP_ABSOLUTE;
            };
            inline OP_JUMP(size_t jump_position, bool jump_down) : jump_position(jump_position) {
                this->op = jump_down ? MICROCPU2_OP_JUMP_DOWN_RELATIVE : MICROCPU2_OP_JUMP_UP_RELATIVE;
            };
            inline void print() override { printf("JMP %s%zu\n", this->op == MICROCPU2_OP_JUMP_ABSOLUTE ? "" : this->op == MICROCPU2_OP_JUMP_DOWN_RELATIVE ? "$pc - " : "$pc + ", jump_position); }
            inline void exe(MicroCpu2 * cpu) override {
                switch(this->op) {
                    case MICROCPU2_OP_JUMP_DOWN_RELATIVE:
                        {
                            if (jump_position == 0) return;
                            size_t tmp = *cpu->current_instruction_pointer;
                            tmp += jump_position;
                            if (tmp <= *cpu->current_instruction_pointer || tmp >= cpu->current_instruction_list->instruction_list.size()) { // overflow
                                throw std::logic_error("illegal relative jump");
                            }
                            *cpu->current_instruction_pointer = tmp;
                            break;
                        }
                    case MICROCPU2_OP_JUMP_UP_RELATIVE:
                        {
                            if (jump_position == 0) return;
                            size_t tmp = *cpu->current_instruction_pointer;
                            tmp -= jump_position;
                            if (tmp >= *cpu->current_instruction_pointer) { // underflow
                                throw std::logic_error("illegal relative jump");
                            }
                            *cpu->current_instruction_pointer = tmp;
                            break;
                        }
                    case MICROCPU2_OP_JUMP_ABSOLUTE:
                        {
                            if (jump_position >= cpu->current_instruction_list->instruction_list.size()) // overflow
                                throw std::logic_error("illegal absolute jump");
                            *cpu->current_instruction_pointer = jump_position;
                            break;
                        }
                    default: break;
                }
            }
        };
        
        struct OP_CONDITIONAL_JUMP : OP_NOP {
            size_t jump_position;
            std::function<bool(void*)> cond;
            inline OP_CONDITIONAL_JUMP(size_t jump_position, const std::function<bool(void*)> & cond) : jump_position(jump_position), cond(cond) {
                this->op = MICROCPU2_OP_CONDITIONAL_JUMP_ABSOLUTE;
            };
            inline OP_CONDITIONAL_JUMP(size_t jump_position, bool jump_down, const std::function<bool(void*)> & cond) : jump_position(jump_position), cond(cond) {
                this->op = jump_down ? MICROCPU2_OP_CONDITIONAL_JUMP_DOWN_RELATIVE : MICROCPU2_OP_CONDITIONAL_JUMP_UP_RELATIVE;
            };
            inline void print() override { printf("JMP_IF_COND <CALL <0x0 or lambda>> %s%zu\n", this->op == MICROCPU2_OP_CONDITIONAL_JUMP_ABSOLUTE ? "" : this->op == MICROCPU2_OP_CONDITIONAL_JUMP_DOWN_RELATIVE ? "$pc - " : "$pc + ", jump_position); }
            inline void exe(MicroCpu2 * cpu) override {
                switch(this->op) {
                    case MICROCPU2_OP_CONDITIONAL_JUMP_DOWN_RELATIVE:
                        {
                            if (jump_position == 0) return;
                            if (!cond(cpu->current_context->user_data)) {
                                (*cpu->current_instruction_pointer)++;
                                return;
                            }
                            size_t tmp = *cpu->current_instruction_pointer;
                            tmp += jump_position;
                            if (tmp <= *cpu->current_instruction_pointer || tmp >= cpu->current_instruction_list->instruction_list.size()) { // overflow
                                throw std::logic_error("illegal relative jump");
                            }
                            *cpu->current_instruction_pointer = tmp;
                            break;
                        }
                    case MICROCPU2_OP_CONDITIONAL_JUMP_UP_RELATIVE:
                        {
                            if (jump_position == 0) return;
                            if (!cond(cpu->current_context->user_data)) {
                                (*cpu->current_instruction_pointer)++;
                                return;
                            }
                            size_t tmp = *cpu->current_instruction_pointer;
                            tmp -= jump_position;
                            if (tmp >= *cpu->current_instruction_pointer) { // underflow
                                throw std::logic_error("illegal relative jump");
                            }
                            *cpu->current_instruction_pointer = tmp;
                            break;
                        }
                    case MICROCPU2_OP_CONDITIONAL_JUMP_ABSOLUTE:
                        {
                            if (!cond(cpu->current_context->user_data)) {
                                (*cpu->current_instruction_pointer)++;
                                return;
                            }
                            if (jump_position >= cpu->current_instruction_list->instruction_list.size()) // overflow
                                throw std::logic_error("illegal absolute jump");
                            *cpu->current_instruction_pointer = jump_position;
                            break;
                        }
                    default: break;
                }
            }
        };
        
        struct OP_PUSH_POP_CONTEXT : OP_NOP {
            std::shared_ptr<Context> target;
            std::function<void(Context*)> after_switch;
            inline OP_PUSH_POP_CONTEXT(Context * target, const std::function<void(Context*)> & after_switch) : target(std::shared_ptr<Context>(target)), after_switch(after_switch) {
                this->op = MICROCPU2_OP_PUSH_POP_CONTEXT;
            };
            inline void print() override { printf("%s_CONTEXT\n", target == nullptr ? "POP" : "PUSH"); }
            inline void exe(MicroCpu2 * cpu) override {
                auto old = cpu->current_context.get();
                if (target.get() != nullptr) {
                    cpu->context_stack.push_back(target);
                    cpu->current_context = cpu->context_stack.back();
                    after_switch(old);
                } else {
                    for (auto begin = cpu->context_stack.begin(), end = cpu->context_stack.end(); begin != end; begin++) {
                        if (begin->get() == old) {
                            cpu->context_stack.erase(begin);
                            if (cpu->context_stack.empty()) {
                                cpu->current_context.reset();
                            } else {
                                cpu->current_context = cpu->context_stack.back();
                            }
                            after_switch(old);
                            return;
                        }
                    }
                    throw std::logic_error("could not find context");
                }
            }
        };

        struct OP_PUSH_POP_INSTRUCTION_LIST : OP_NOP {
            InstructionList * target;
            std::function<void(InstructionList*)> after_switch;
            bool should_increment_instruction_pointer;
            inline OP_PUSH_POP_INSTRUCTION_LIST(bool should_increment_instruction_pointer, InstructionList * target, const std::function<void(InstructionList*)> & after_switch) : should_increment_instruction_pointer(should_increment_instruction_pointer), target(target), after_switch(after_switch) {
                this->op = MICROCPU2_OP_PUSH_POP_INSTRUCTION_LIST;
            };
            inline void print() override { printf("%s_INSTRUCTION_LIST\n", target == nullptr ? "POP" : "PUSH"); }
            inline void exe(MicroCpu2 * cpu) override {
                auto old = cpu->current_instruction_list;
                if (target != nullptr) {
                    if (cpu->current_instruction_pointer != nullptr && should_increment_instruction_pointer) {
                        (*cpu->current_instruction_pointer)++;
                    }
                    cpu->instruction_list_queue.push_back({target, 0});
                    cpu->current_instruction_list = target;
                    cpu->current_instruction_pointer = &cpu->instruction_list_queue.back().second;
                } else {
                    cpu->instruction_list_queue.pop_back();
                    if (cpu->instruction_list_queue.empty()) {
                        cpu->current_instruction_list = nullptr;
                        cpu->current_instruction_pointer = nullptr;
                    } else {
                        auto & i = cpu->instruction_list_queue.back();
                        cpu->current_instruction_list = i.first;
                        cpu->current_instruction_pointer = &i.second;
                    }
                }
                after_switch(old);
            }
        };

        // instruction list
        //
        std::vector<std::shared_ptr<OP_NOP>> instruction_list;

        private:
        
        inline void after_op(OP_NOP * op) {
            instruction_list.insert(instruction_list.end(), std::shared_ptr<OP_NOP>(op));
        }
        
        public:

        inline void after(const std::function<void(void*)> & f) {
            after_op(new OP_EXE(f));
        }
        
        inline void insert_relative_jump_after(size_t jmp, bool is_down) {
            after_op(new OP_JUMP(jmp, is_down));
        }
    
        inline void insert_absolute_jump_after(size_t jmp) {
            after_op(new OP_JUMP(jmp));
        }
    
        inline void insert_relative_conditional_jump_after(size_t jmp, bool is_down, const std::function<bool(void*)> & cond) {
            after_op(new OP_CONDITIONAL_JUMP(jmp, is_down, cond));
        }
    
        inline void insert_absolute_conditional_jump_after(size_t jmp, const std::function<bool(void*)> & cond) {
            after_op(new OP_CONDITIONAL_JUMP(jmp, cond));
        }
        
        inline void insert_push_context_after(Context * context, const std::function<void(Context*)> & before_switch) {
            after_op(new OP_PUSH_POP_CONTEXT(context, before_switch));
        }
        
        inline void insert_push_context_after(Context * context) {
            after_op(new OP_PUSH_POP_CONTEXT(context, [](Context*){}));
        }

        inline void insert_pop_context_after(const std::function<void(Context*)> & after_switch) {
            after_op(new OP_PUSH_POP_CONTEXT(nullptr, after_switch));
        }
        
        inline void insert_pop_context_after() {
            after_op(new OP_PUSH_POP_CONTEXT(nullptr, [](Context*){}));
        }

        inline void insert_push_instruction_list_after(InstructionList * list, const std::function<void(InstructionList*)> & after_switch) {
            after_op(new OP_PUSH_POP_INSTRUCTION_LIST(true, list, after_switch));
        }

        inline void insert_push_instruction_list_after(InstructionList * list) {
            after_op(new OP_PUSH_POP_INSTRUCTION_LIST(true, list, [](InstructionList*){}));
        }
        
        inline void insert_pop_instruction_list_after(const std::function<void(InstructionList*)> & after_switch) {
            after_op(new OP_PUSH_POP_INSTRUCTION_LIST(true, nullptr, after_switch));
        }

        inline void insert_pop_instruction_list_after() {
            after_op(new OP_PUSH_POP_INSTRUCTION_LIST(true, nullptr, [](InstructionList*){}));
        }
    };

    inline const Context * get_current_context() {
        return current_context.get();
    };

    inline const InstructionList * get_current_instruction_list() {
        return current_instruction_list;
    };

    inline size_t get_current_instruction_pointer() {
        return *current_instruction_pointer;
    };
    
    bool print_instruction_list = false;

    private:

    #define MICROCPU2_MACRO_AS(T) static_cast<InstructionList::T&>(it)
    

    inline void exe_from_current(void * initial_value) {
    
        // create main context
        //
        InstructionList::OP_PUSH_POP_CONTEXT(new Context(initial_value), [](Context*){}).exe(this);

        while(current_instruction_list != nullptr) {
            if (print_instruction_list) print_instructions("before executing:");
            auto & it = *current_instruction_list->instruction_list[*current_instruction_pointer];
            switch(it.op) {
                case MICROCPU2_OP_EXE:
                {
                    auto old = current_instruction_pointer;
                    MICROCPU2_MACRO_AS(OP_EXE).exe(this);
                    
                    // only increment the instruction pointer if the current instruction pointer has not changed
                    //
                    // the current instruction pointer may be changed at execution time via 'cpu.push_instruction_list(list)'
                    //
                    if (old == current_instruction_pointer) (*current_instruction_pointer)++;
                    break;
                }
                case MICROCPU2_OP_JUMP_DOWN_RELATIVE:
                case MICROCPU2_OP_JUMP_UP_RELATIVE:
                case MICROCPU2_OP_JUMP_ABSOLUTE:
                {
                    MICROCPU2_MACRO_AS(OP_JUMP).exe(this);
                    break;
                }
                case MICROCPU2_OP_CONDITIONAL_JUMP_DOWN_RELATIVE:
                case MICROCPU2_OP_CONDITIONAL_JUMP_UP_RELATIVE:
                case MICROCPU2_OP_CONDITIONAL_JUMP_ABSOLUTE:
                {
                    MICROCPU2_MACRO_AS(OP_CONDITIONAL_JUMP).exe(this);
                    break;
                }
                case MICROCPU2_OP_PUSH_POP_CONTEXT:
                {
                    MICROCPU2_MACRO_AS(OP_PUSH_POP_CONTEXT).exe(this);
                    (*current_instruction_pointer)++;
                    break;
                }
                case MICROCPU2_OP_PUSH_POP_INSTRUCTION_LIST:
                {
                    MICROCPU2_MACRO_AS(OP_PUSH_POP_INSTRUCTION_LIST).exe(this);
                    break;
                }
                case MICROCPU2_OP_NOP:
                default:
                {
                    (*current_instruction_pointer)++;
                    break;
                }
            }
        }
        InstructionList::OP_PUSH_POP_CONTEXT(nullptr, [](Context*){}).exe(this);
    }
    
    friend InstructionList;
    
    InstructionList* current_instruction_list = nullptr;
    size_t * current_instruction_pointer = nullptr;
    std::deque<std::pair<InstructionList*, size_t>> instruction_list_queue;

    std::shared_ptr<Context> current_context;
    std::deque<std::shared_ptr<Context>> context_stack;
    
    std::deque<std::shared_ptr<InstructionList>> synthetic_instruction_list_queue;
    size_t * synthetic_old_instruction_pointer = nullptr;

    public:
    
    inline void push_instruction_list(InstructionList * list, const std::function<void(InstructionList*)> & after_switch) {
        InstructionList * synthetic_list;
        if (
            synthetic_instruction_list_queue.empty()
            || current_instruction_pointer != synthetic_old_instruction_pointer
            || (synthetic_old_instruction_pointer != nullptr && *current_instruction_pointer != *synthetic_old_instruction_pointer)
        ) {
            // we changes instructions, push a new list
            //
            synthetic_instruction_list_queue.push_back(std::shared_ptr<InstructionList>(new InstructionList()));
            
            // update pointers
            //
            synthetic_old_instruction_pointer = current_instruction_pointer;
            synthetic_list = synthetic_instruction_list_queue.back().get();
            
            // append the pop instruction to the end of the list
            //
            synthetic_list->insert_pop_instruction_list_after([=](InstructionList*list) {
                for (auto begin = synthetic_instruction_list_queue.begin(), end = synthetic_instruction_list_queue.end(); begin != end; begin++) {
                    if (begin->get() == list) {
                        after_switch(list);
                        synthetic_instruction_list_queue.erase(begin);
                        return;
                    }
                }
                throw std::logic_error("could not find synthetic instruction");
            });
            
            // set the synthetic list as current
            //
            InstructionList::OP_PUSH_POP_INSTRUCTION_LIST(true, synthetic_list, [](InstructionList*){}).exe(this);

            // update the synthetic pointer to point to the synthetic list we just added
            //
            synthetic_old_instruction_pointer = current_instruction_pointer;
        } else {
            // we are building on top of an unchanged instruction
            //
            synthetic_list = synthetic_instruction_list_queue.back().get();
        }
        
        // insert the list to the synthetic list before last pop instruction
        //
        auto it = synthetic_list->instruction_list.end();
        it--;
        synthetic_list->instruction_list.insert(it, std::shared_ptr<InstructionList::OP_NOP>(new InstructionList::OP_PUSH_POP_INSTRUCTION_LIST(true, list, [](InstructionList*){})));
    }

    inline void push_instruction_list(InstructionList * list) {
        push_instruction_list(list, [](InstructionList*){});
    }

    inline void exe(InstructionList * list, void * user_data) {
        push_instruction_list(list);
        exe_from_current(user_data);
    }

    inline void exe(InstructionList * list) { exe(list, nullptr); }

    inline void print_instructions(const char * m) const {
        printf("%s\n", m);
        printf("[ context: %p ]\n", current_context.get());
        printf("[ instruction list: %p ]\n", current_instruction_list);
        if (current_instruction_list == nullptr) return;
        for (size_t i = 0; i < current_instruction_list->instruction_list.size(); i++) {
            if (i == *current_instruction_pointer) printf(" -> ");
            else printf("    ");
            current_instruction_list->instruction_list[i]->print();
        }
    }

    inline void print_instructions() const { print_instructions("instruction list:"); }
    
};

#endif