#ifndef COMPOSABLE_LIST_H
#define COMPOSABLE_LIST_H

#include <memory>
#include <functional>
#include <list>

template <typename T>
struct Composable_Function_Holder {
    std::function<T(T&)> data;

    Composable_Function_Holder(const std::function<T(T)> & func) : data(func) {}

    T operator()(T&v) {
        return data(v);
    }
};

template <>
struct Composable_Function_Holder<void> {
    std::function<void()> data;

    Composable_Function_Holder(const std::function<void()> & func) : data(func) {}

    void operator()() {
        data();
    }
};

template <typename T>
class Composable_List final {
    std::shared_ptr<std::list<std::shared_ptr<Composable_Function_Holder<T>>>> list;
    typename std::list<std::shared_ptr<Composable_Function_Holder<T>>>::iterator iterator;

    Composable_List(Composable_List<T> * parent) : list(parent->list) {}

    public:
    
    Composable_List() {
        list.reset(new std::list<std::shared_ptr<Composable_Function_Holder<T>>>());
        iterator = list->insert(list->begin(), std::shared_ptr<Composable_Function_Holder<T>>());
    }

    template <typename Item>
    Composable_List(const Item & f) {
        list.reset(new std::list<std::shared_ptr<Composable_Function_Holder<T>>>());
        iterator = list->insert(list->begin(), std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
    }

    template <typename Item>
    std::shared_ptr<Composable_List<T>> before(const Item & f) {
        auto a = std::shared_ptr<Composable_List<T>>(new Composable_List<T>(this));
        a->iterator = list->insert(iterator, std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
        return a;
    }

    template <typename Item>
    std::shared_ptr<Composable_List<T>> after(const Item & f) {
        auto a = std::shared_ptr<Composable_List<T>>(new Composable_List<T>(this));
        auto copy = iterator;
        copy++;
        a->iterator = list->insert(copy, std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
        return a;
    }

    template <typename U = T, typename X = typename std::enable_if<std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    void visit() {
        for (auto current = iterator, end = list->end(); current != end; current++) {
            if (*current != nullptr) {
                (*current)->operator()();
            }
        }
    }

    template <typename U = T, typename X = typename std::enable_if<std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    void visitFromStart() {
        for (auto current = list->begin(), end = list->end(); current != end; current++) {
            if (*current != nullptr) {
                (*current)->operator()();
            }
        }
    }

    template <typename U = T, typename X = typename std::enable_if<!std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    U visit(const U & initial_value) {
        U accumulator = initial_value;
        for (auto current = iterator; current != list->end(); current++) {
            if (*current != nullptr) {
                accumulator = (*current)->operator()(accumulator);
            }
        }
        return accumulator;
    }

    template <typename U = T, typename X = typename std::enable_if<!std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    U visitFromStart(const U & initial_value) {
        U accumulator = initial_value;
        for (auto current = list->begin(); current != list->end(); current++) {
            if (*current != nullptr) {
                accumulator = (*current)->operator()(accumulator);
            }
        }
        return accumulator;
    }
};

template <typename T>
class Composable_List_COW final {
    std::shared_ptr<std::list<std::shared_ptr<Composable_Function_Holder<T>>>> list;
    std::shared_ptr<std::list<uint64_t>> list_ids;
    uint64_t id = 0;

    std::shared_ptr<Composable_List_COW<T>> clone() {
        auto a = std::shared_ptr<Composable_List_COW<T>>(new Composable_List_COW<T>());
        a->list->clear();
        a->list_ids->clear();
        for (auto current = list->begin(), end = list->end(); current != end; current++) {
            a->list->insert(a->list->end(), *current);
        }
        for (auto current = list_ids->begin(), end = list_ids->end(); current != end; current++) {
            a->list_ids->insert(a->list_ids->end(), *current);
        }
        return a;
    }

    public:
    
    Composable_List_COW() {
        list.reset(new std::list<std::shared_ptr<Composable_Function_Holder<T>>>());
        list->insert(list->begin(), std::shared_ptr<Composable_Function_Holder<T>>());
        list_ids.reset(new std::list<uint64_t>());
        list_ids->insert(list_ids->begin(), id);
    }

    template <typename Item>
    Composable_List_COW(const Item & f) {
        list.reset(new std::list<std::shared_ptr<Composable_Function_Holder<T>>>());
        list->insert(list->begin(), std::shared_ptr<Composable_Function_Holder<T>>());
        list_ids.reset(new std::list<uint64_t>());
        list_ids->insert(list_ids->begin(), id);
    }

    template <typename Item>
    std::shared_ptr<Composable_List_COW<T>> before(const Item & f) {
        auto a = clone();
        a->list->push_front(std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
        a->id = id + 1;
        a->list_ids->push_front(a->id);
        return a;
    }

    template <typename Item>
    std::shared_ptr<Composable_List_COW<T>> after(const Item & f) {
        auto a = clone();
        a->list->push_back(std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
        a->id = id + 1;
        a->list_ids->push_back(a->id);
        return a;
    }

    template <typename Item>
    std::shared_ptr<Composable_List_COW<T>> before(std::shared_ptr<Composable_List_COW<T>> list, const Item & f) {
        auto a = std::shared_ptr<Composable_List_COW<T>>(new Composable_List_COW<T>());
        a->list->clear();
        a->list_ids->clear();

        a->id = id + 1;

        uint64_t index = 0;
        uint64_t target_index = 0;

        for (auto current = list_ids->begin(), end = list_ids->end(); current != end; current++, index++) {
            if (*current == list->id) {
                target_index = index;
                a->list_ids->insert(a->list_ids->end(), a->id);
            }
            a->list_ids->insert(a->list_ids->end(), *current);
        }

        index = 0;

        for (auto current = this->list->begin(), end = this->list->end(); current != end; current++, index++) {
            if (index == target_index) {
                a->list->insert(a->list->end(), std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
            }
            a->list->insert(a->list->end(), *current);
        }

        return a;
    }

    template <typename Item>
    std::shared_ptr<Composable_List_COW<T>> after(std::shared_ptr<Composable_List_COW<T>> list, const Item & f) {
        auto a = std::shared_ptr<Composable_List_COW<T>>(new Composable_List_COW<T>());
        a->list->clear();
        a->list_ids->clear();

        a->id = id + 1;

        uint64_t index = 0;
        uint64_t target_index = 0;

        for (auto current = list_ids->begin(), end = list_ids->end(); current != end; current++, index++) {
            a->list_ids->insert(a->list_ids->end(), *current);
            if (*current == list->id) {
                target_index = index;
                a->list_ids->insert(a->list_ids->end(), a->id);
            }
        }

        index = 0;

        for (auto current = this->list->begin(), end = this->list->end(); current != end; current++, index++) {
            a->list->insert(a->list->end(), *current);
            if (index == target_index) {
                a->list->insert(a->list->end(), std::shared_ptr<Composable_Function_Holder<T>>(new Composable_Function_Holder<T>(f)));
            }
        }

        return a;
    }

    template <typename U = T, typename X = typename std::enable_if<std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    void visit() {
        bool can_call = false;
        auto current = list->begin();
        auto current_id = list_ids->begin();
        auto end = list->end();
        while (current != end) {
            if (can_call) {
                (*current)->operator()();
            } else {
                if (*current_id == id) {
                    can_call = true;
                    (*current)->operator()();
                } else {
                    current_id++;
                }
            }
            current++;
        }
    }

    template <typename U = T, typename X = typename std::enable_if<std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    void visitFromStart() {
        for (auto current = list->begin(), end = list->end(); current != end; current++) {
            (*current)->operator()();
        }
    }

    template <typename U = T, typename X = typename std::enable_if<!std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    U visit(const U & initial_value) {
        U accumulator = initial_value;
        bool can_call = false;
        auto current = list->begin();
        auto current_id = list_ids->begin();
        auto end = list->end();
        while (current != end) {
            if (can_call) {
                accumulator = (*current)->operator()(accumulator);
            } else {
                if (*current_id == id) {
                    can_call = true;
                    accumulator = (*current)->operator()(accumulator);
                } else {
                    current_id++;
                }
            }
            current++;
        }
        return accumulator;
    }

    template <typename U = T, typename X = typename std::enable_if<!std::is_same<void, U>::value && std::is_same<U, T>::value>::type>
    U visitFromStart(const U & initial_value) {
        U accumulator = initial_value;
        for (auto current = list->begin(), end = list->end(); current != end; current++) {
            accumulator = (*current)->operator()(accumulator);
        }
        return accumulator;
    }
};

#endif
