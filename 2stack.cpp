#pragma once

#include "1deque.cpp"
#include <utility>

template <typename T, typename Container = Deque<T>>
class Stack {
private:
    Container container;

public:
    template <typename... Args>
    Stack(Args&&... args) : container(std::forward<Args>(args)...) {}

    bool empty() const {
        return container.empty();
    }

    size_t size() const {
        return container.size();
    }

    T& top() {
        return container.pop_back();
    }

    const T& top() const {
        return container.pop_back();
    }

    void push(const T& value) {
        container.push_back(value);
    }

    void push(T&& value) {
        container.push_back(std::move(value));
    }

    void pop() {
        container.pop_back();
    }
};
