#include <MicroCpu2.h>
#include <stdio.h>

#define EXPECT_TRUE(cond) if ((cond) != true) printf("%s failed assertion: [ (" #cond ") == true ] [ ("#cond") was [ false ] ] \n", __FUNCTION__)

#define EXPECT_FALSE(cond) if ((cond) != false) printf("%s failed assertion: [ (" #cond ") == false ] [ ("#cond") was [ true ] ] \n", __FUNCTION__)

#define EXPECT_EQ(cond, value) if ((cond) != value) printf("%s failed assertion: [ (" #cond ") == " #value " ] \n", __FUNCTION__)

// ensures we can execute an instruction - 'foo()'
//
void test_1() {
    MicroCpu2 cpu;
    MicroCpu2::InstructionList list;
    bool executed = false;
    list.after([&](void*){ executed = true; });
    list.insert_pop_instruction_list_after();
    cpu.exe(&list, nullptr);
    EXPECT_TRUE(executed);
}

// ensures we can return a value to the previous instruction - 'ret = foo()'
//
void test_2() {
    MicroCpu2 cpu;
    MicroCpu2::InstructionList list1, list2;
    
    struct Data {
        bool ret = false;
    } data;

    list2.insert_push_context_after(new MicroCpu2::Context(new Data, [](void*p){delete static_cast<Data*>(p);}));
    list2.after([&](void*u) { static_cast<Data*>(u)->ret = true; });
    list2.insert_pop_context_after([&](MicroCpu2::Context * old) {
        Data * current = static_cast<Data*>(cpu.get_current_context()->user_data);
        Data * old_ = static_cast<Data*>(old->user_data);
        current->ret = old_->ret;
    });
    list2.insert_pop_instruction_list_after();

    list1.insert_push_context_after(new MicroCpu2::Context(&data));
    list1.after([&](void*u) { cpu.push_instruction_list(&list2); });
    list1.insert_pop_context_after();
    list1.insert_pop_instruction_list_after();
    
    cpu.exe(&list1);
    
    EXPECT_TRUE(data.ret);
}

// ensures we can return a value to the previous instruction while maintaining order of insertion
//
void test_3() {
    MicroCpu2 cpu;
    MicroCpu2::InstructionList list1, list2, list3;
    
    struct Data {
        bool e2 = false;
        bool e3 = false;
        int ret = 0;
    } data;

    list2.insert_push_context_after(new MicroCpu2::Context(new Data, [](void*p){delete static_cast<Data*>(p);}));
    list2.after([&](void*u) { static_cast<Data*>(u)->ret = 5; });
    list2.insert_pop_context_after([&](MicroCpu2::Context * old) {
        Data * current = static_cast<Data*>(cpu.get_current_context()->user_data);
        Data * old_ = static_cast<Data*>(old->user_data);
        current->e2 = true;
        current->ret = old_->ret;
    });
    list2.insert_pop_instruction_list_after();

    list3.insert_push_context_after(new MicroCpu2::Context(new Data, [](void*p){delete static_cast<Data*>(p);}));
    list3.after([&](void*u) { static_cast<Data*>(u)->ret = 4; });
    list3.insert_pop_context_after([&](MicroCpu2::Context * old) {
        Data * current = static_cast<Data*>(cpu.get_current_context()->user_data);
        Data * old_ = static_cast<Data*>(old->user_data);
        current->e3 = true;
        current->ret = old_->ret;
    });
    list3.insert_pop_instruction_list_after();

    list1.insert_push_context_after(new MicroCpu2::Context(&data));

    list1.after([&](void*u) { cpu.push_instruction_list(&list2); cpu.push_instruction_list(&list3); });

    list1.insert_pop_context_after();
    list1.insert_pop_instruction_list_after();
    
    cpu.exe(&list1);
    
    EXPECT_TRUE(data.e2);
    EXPECT_TRUE(data.e3);
    EXPECT_EQ(data.ret, 4);
}

int main() {
    test_1();
    test_2();
    test_3();
    return 0;
}
