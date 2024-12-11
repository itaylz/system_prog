#pragma once
#include <vector>
#include <memory>

template <typename T>
class Node {
public:
    T data;
    std::vector<std::shared_ptr<Node<T>>> children;

    Node(const T& value) : data(value) {}

    T get_value() const {
        return data;
    }
    void set_value(T value) {
        data = value;
    }
};
