#ifndef ZLANG_MICROCPU_H
#define ZLANG_MICROCPU_H

#include <memory>
#include <functional>
#include <list>
#include <stdexcept>

enum MICROCPU_OP {
    MICROCPU_OP_NOP,
    MICROCPU_OP_EXE,
    MICROCPU_OP_JUMP_DOWN_RELATIVE,
    MICROCPU_OP_JUMP_UP_RELATIVE,
    MICROCPU_OP_JUMP_ABSOLUTE,
    MICROCPU_OP_CONTEXT_SWITCH,
    MICROCPU_OP_DESTROY_THREAD_CONTEXT,
};

// https://github.com/royvandam/rtti

struct MicroCpu final {

    struct ThreadContext {

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
        inline ThreadContext() : user_data(nullptr), deleter([](void*p){}) {}
        inline ThreadContext(void * user_data) : user_data(user_data), deleter([](void*p){}) {}
        inline ThreadContext(void * user_data, std::function<void(void*)> deleter) : user_data(user_data), deleter(deleter) {}
        virtual inline ~ThreadContext() { deleter(user_data); }
    };

    private:
    
    struct OP_NOP;
    
    // instruction list
    //
    size_t current_instruction_pointer = 0;
    std::vector<std::shared_ptr<OP_NOP>> instruction_list;
    
    // thread context list
    //
    ThreadContext * current_thread = nullptr;
    std::vector<std::shared_ptr<ThreadContext>> thread_list;

    public:

    inline ThreadContext * create_thread_context(void * user_data, std::function<void(void*)> deleter) {
        std::shared_ptr<ThreadContext> thread { new ThreadContext(user_data, deleter) };
        thread_list.emplace_back(thread);
        return thread.get();
    }

    inline ThreadContext * create_thread_context(void * user_data) {
        return create_thread_context(user_data, [](void*p){});
    }

    inline ThreadContext * create_thread_context() { return create_thread_context(nullptr); }

    inline void destroy_thread_context(ThreadContext * context) {
        for (auto b = thread_list.begin(), e = thread_list.end(); b != e; b++) {
            if (b->get() == context) {
                thread_list.erase(b);
                break;
            }
        }
    }
    
    inline ThreadContext * get_current_thread_context() {
        return current_thread;
    }
    
    inline size_t get_current_instruction_pointer() {
        return current_instruction_pointer;
    };

    private:
    
    struct OP_NOP {
        MICROCPU_OP op;
        inline OP_NOP() { op = MICROCPU_OP_NOP; }
        inline virtual void print() { printf("NOP\n"); }
        inline virtual void exe(MicroCpu * cpu) {}
        inline virtual ~OP_NOP() {}
    };
    
    struct OP_EXE : OP_NOP {
        std::function<void(void*)> f;
        inline OP_EXE(const std::function<void(void*)> & f) : f(f) { this->op = MICROCPU_OP_EXE; };
        inline void print() override { f.target<void(*)(void*)>() == nullptr ? printf("CALL <0x0 or lambda>\n") : printf("CALL %p\n", f.target<void(*)(void*)>()); }
        inline void exe(MicroCpu * cpu) override {
            f.operator()(cpu->current_thread->user_data);
        }
    };
    
    struct OP_JUMP : OP_NOP {
        size_t jump_position;
        inline OP_JUMP(size_t jump_position) : jump_position(jump_position) {
            this->op = MICROCPU_OP_JUMP_ABSOLUTE;
        };
        inline OP_JUMP(size_t jump_position, bool jump_down) : jump_position(jump_position) {
            this->op = jump_down ? MICROCPU_OP_JUMP_DOWN_RELATIVE : MICROCPU_OP_JUMP_UP_RELATIVE;
        };
        inline void print() override { printf("JMP %s%zu\n", this->op == MICROCPU_OP_JUMP_ABSOLUTE ? "" : this->op == MICROCPU_OP_JUMP_DOWN_RELATIVE ? "$pc - " : "$pc + ", jump_position); }
        inline void exe(MicroCpu * cpu) override {
            switch(this->op) {
                case MICROCPU_OP_JUMP_DOWN_RELATIVE:
                    {
                        if (jump_position == 0) return;
                        size_t tmp = cpu->current_instruction_pointer;
                        tmp += jump_position;
                        if (tmp <= cpu->current_instruction_pointer || tmp >= cpu->instruction_list.size()) { // overflow
                            throw std::logic_error("illegal relative jump");
                        }
                        cpu->current_instruction_pointer = tmp;
                        break;
                    }
                case MICROCPU_OP_JUMP_UP_RELATIVE:
                    {
                        if (jump_position == 0) return;
                        size_t tmp = cpu->current_instruction_pointer;
                        tmp -= jump_position;
                        if (tmp >= cpu->current_instruction_pointer) { // underflow
                            throw std::logic_error("illegal relative jump");
                        }
                        cpu->current_instruction_pointer = tmp;
                        break;
                    }
                case MICROCPU_OP_JUMP_ABSOLUTE:
                    {
                        if (jump_position >= cpu->instruction_list.size()) // overflow
                            throw std::logic_error("illegal absolute jump");
                        cpu->current_instruction_pointer = jump_position;
                        break;
                    }
                default: break;
            }
        }
    };
    
    struct OP_CONTEXT_SWITCH : OP_NOP {
        ThreadContext * target;
        inline OP_CONTEXT_SWITCH(ThreadContext * target) : target(target) {
            if (target == nullptr)
                throw std::logic_error("cannot create a nullptr context switch");
            this->op = MICROCPU_OP_CONTEXT_SWITCH;
        };
        inline void print() override { printf("SET_CONTEXT %p\n", target); }
        inline void exe(MicroCpu * cpu) override { cpu->current_thread = target; }
    };
    
    struct OP_DESTROY_THREAD_CONTEXT : OP_NOP {
        ThreadContext * target;
        inline OP_DESTROY_THREAD_CONTEXT(ThreadContext * target) : target(target) {
            this->op = MICROCPU_OP_DESTROY_THREAD_CONTEXT;
        };
        inline void print() override { printf("DELETE_CONTEXT %p\n", target); }
        inline void exe(MicroCpu * cpu) override { cpu->destroy_thread_context(target); }
    };

    public:
    
    inline MicroCpu() { current_instruction_pointer = 0; }

    inline void print_instructions(const char * m) {
        printf("%s\n", m);
        for (size_t i = 0; i < instruction_list.size(); i++) {
            if (i == current_instruction_pointer) printf(" -> ");
            else printf("    ");
            instruction_list[i]->print();
        }
    }

    inline void print_instructions() { print_instructions("instruction list:"); }

    private:

    size_t insert_increment = 0;
    
    inline void after_op(OP_NOP * op) {
        if (current_thread != nullptr) {
            instruction_list.insert(instruction_list.begin() + current_instruction_pointer + insert_increment + 1, std::shared_ptr<OP_NOP>(op));
            insert_increment++;
        } else {
            instruction_list.insert(instruction_list.end(), std::shared_ptr<OP_NOP>(op));
        }
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

    inline void insert_context_switch_after(ThreadContext * context) {
        after_op(new OP_CONTEXT_SWITCH(context));
    }

    inline void insert_destroy_thread_context_after(ThreadContext * context) {
        after_op(new OP_DESTROY_THREAD_CONTEXT(context));
    }

    #define MICROCPU_MACRO_AS(T) static_cast<T&>(it)
    
    private:
    
    inline void exe_from_current(void * initial_value) {

        // create main thread context
        //
        current_thread = create_thread_context(initial_value);

        while(current_instruction_pointer < instruction_list.size()) {
            insert_increment = 0;
            auto & it = *instruction_list[current_instruction_pointer];
            switch(it.op) {
                case MICROCPU_OP_EXE:
                {
                    MICROCPU_MACRO_AS(OP_EXE).exe(this);
                    current_instruction_pointer++;
                    continue;
                }
                case MICROCPU_OP_JUMP_DOWN_RELATIVE:
                case MICROCPU_OP_JUMP_UP_RELATIVE:
                case MICROCPU_OP_JUMP_ABSOLUTE:
                {
                    MICROCPU_MACRO_AS(OP_JUMP).exe(this);
                    continue;
                }
                case MICROCPU_OP_CONTEXT_SWITCH:
                {
                    MICROCPU_MACRO_AS(OP_CONTEXT_SWITCH).exe(this);
                    current_instruction_pointer++;
                    continue;
                }
                case MICROCPU_OP_DESTROY_THREAD_CONTEXT:
                {
                    MICROCPU_MACRO_AS(OP_DESTROY_THREAD_CONTEXT).exe(this);
                    current_instruction_pointer++;
                    continue;
                }
                case MICROCPU_OP_NOP:
                default:
                {
                    current_instruction_pointer++;
                    continue;
                }
            }
        }
    }
    
    public:

    inline void exeFromStart(void * user_data) {
        current_instruction_pointer = 0;
        exe_from_current(user_data);
    }

    inline void exeFromStart() { exeFromStart(nullptr); }
};

#endif