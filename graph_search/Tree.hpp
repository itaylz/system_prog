#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <algorithm>
#include "Node.hpp"
#include <iostream>
#include <utility>

template <typename T>
class BaseIterator {
protected:
    std::shared_ptr<Node<T>> _current; // Holds the current node
public:
    virtual ~BaseIterator() = default; // Virtual destructor
    virtual BaseIterator& operator++() = 0; // Pure virtual increment operator
    virtual bool operator!=(const BaseIterator& other) const = 0; // Pure virtual not equal operator
    virtual Node<T>* operator*() const = 0; // Pure virtual dereference operator
    virtual Node<T>* operator->() const = 0; // Pure virtual member access operator
};

template <typename T>
class BinaryTreeIterator : public BaseIterator<T> {
protected:
    std::stack<std::shared_ptr<Node<T>>> _node_stack; // Stack to hold nodes

    void traverse_left(std::shared_ptr<Node<T>> node) { // Helper function to traverse left subtree
        while (node != nullptr) {
            _node_stack.push(node); // Pushes the node to the stack
            if (!node->children.empty()) {
                node = node->children[0]; // Move to the left child
            } else {
                node = nullptr;
            }
        }
    }
};

template <typename T, int K = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root; // Root node of the tree

    void pre_order_helper(const std::shared_ptr<Node<T>>& node, std::vector<std::shared_ptr<Node<T>>>& nodes) const { // Pre-order traversal helper function
        if (!node) return;
        nodes.push_back(node); // Visit the current node
        for (const auto& child : node->children) {
            pre_order_helper(child, nodes); // Recur on children
        }
    }

    void post_order_helper(const std::shared_ptr<Node<T>>& node, std::vector<std::shared_ptr<Node<T>>>& nodes) const { // Post-order traversal helper function
        if (!node) return;
        for (const auto& child : node->children) {
            post_order_helper(child, nodes); // Recur on children
        }
        nodes.push_back(node); // Visit the current node
    }

    void in_order_helper(const std::shared_ptr<Node<T>>& node, std::vector<std::shared_ptr<Node<T>>>& nodes) const { // In-order traversal helper function (only for binary trees)
        if (!node || K != 2) return;
        if (!node->children.empty()) {
            in_order_helper(node->children[0], nodes); // Recur on left child
        }
        nodes.push_back(node); // Visit the current node
        if (node->children.size() > 1) {
            in_order_helper(node->children[1], nodes); // Recur on right child
        }
    }

    void myHeapHelper(std::shared_ptr<Node<T>> node) { // Custom heap operation helper function
        if (!node) return;

        std::priority_queue<T, std::vector<T>, std::greater<T>> minHeap; // Min-heap to store node values
        std::queue<std::shared_ptr<Node<T>>> nodeQueue; // Queue for level-order traversal
        nodeQueue.push(node);

        while (!nodeQueue.empty()) {
            auto current = nodeQueue.front(); // Get the front node from the queue
            nodeQueue.pop();
            minHeap.push(current->get_value()); // Push the node value to the heap

            for (const auto& child : current->children) {
                nodeQueue.push(child); // Enqueue the children
            }
        }

        std::queue<std::shared_ptr<Node<T>>> fillQueue; // Queue to refill the tree with sorted values
        fillQueue.push(node);
        while (!fillQueue.empty()) {
            auto current = fillQueue.front(); // Get the front node from the queue
            fillQueue.pop();
            current->set_value(minHeap.top()); // Set the node value to the top of the heap
            minHeap.pop();

            for (const auto& child : current->children) {
                fillQueue.push(child); // Enqueue the children
            }
        }
    }

public:
    Tree() : root(nullptr) {} // Constructor initializes the root to nullptr

    void add_root(const Node<T>& root_node) { // Adds a root node to the tree
        root = std::make_shared<Node<T>>(root_node);
    }

    void add_sub_node(const Node<T>& parent_node, const Node<T>& sub_node) { // Adds a sub-node to a given parent node
        auto parent = find_node(root, parent_node); // Find the parent node

        if (!parent) {
            throw std::runtime_error("Parent node does not exist"); // Error if parent node not found
        }
        if (parent->children.size() > K) {
            throw std::runtime_error("Cannot add more children to this node"); // Error if children exceed the limit
        }
        if (parent && parent->children.size() < K) {
            parent->children.push_back(std::make_shared<Node<T>>(sub_node)); // Add the sub-node to the parent
        }
    }

    std::shared_ptr<Node<T>> find_node(const std::shared_ptr<Node<T>>& node, const Node<T>& target) { // Finds a node in the tree
        if (!node) return nullptr;
        if (node->data == target.data) return node; // Node found
        for (const auto& child : node->children) {
            auto found = find_node(child, target); // Recur on children
            if (found) return found; // Node found in children
        }
        return nullptr;
    }

    std::shared_ptr<Node<T>> get_root() const { // Returns the root node
        return root;
    }

    void myHeap() { // Custom heap operation
        myHeapHelper(root);
    }

    // Pre-Order Iterator (Binary Tree)
    class BinaryPreOrderIterator : public BinaryTreeIterator<T> {
    public:
        BinaryPreOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                this->_node_stack.push(root); // Push the root node to the stack
                this->_current = root; // Set the current node to root
            }
        }

        BinaryPreOrderIterator& operator++() override { // Pre-order increment operator
            if (!this->_current) return *this;

            for (auto it = this->_current->children.rbegin(); it != this->_current->children.rend(); ++it) {
                this->_node_stack.push(*it); // Push the children in reverse order
            }

            if (!this->_node_stack.empty()) {
                this->_current = this->_node_stack.top(); // Set the current node to the top of the stack
                this->_node_stack.pop();
            } else {
                this->_current = nullptr; // No more nodes to visit
            }

            return *this;
        }

        bool operator!=(const BaseIterator<T>& other) const override { // Not equal operator
            return this->_current != static_cast<const BinaryPreOrderIterator*>(&other)->_current;
        }

        Node<T>* operator*() const override { // Dereference operator
            return this->_current.get();
        }

        Node<T>* operator->() const override { // Member access operator
            return this->_current.get();
        }
    };

    // In-Order Iterator (Binary Tree)
    class BinaryInOrderIterator : public BinaryTreeIterator<T> {
    public:
        BinaryInOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                this->traverse_left(root); // Traverse to the leftmost node
                if (!this->_node_stack.empty()) {
                    this->_current = this->_node_stack.top(); // Set the current node to the top of the stack
                    this->_node_stack.pop();
                }
            }
        }

        BinaryInOrderIterator& operator++() override { // In-order increment operator
            if (!this->_current) return *this;

            if (this->_current->children.size() > 1) {
                this->traverse_left(this->_current->children[1]); // Traverse the right child
            }

            if (!this->_node_stack.empty()) {
                this->_current = this->_node_stack.top(); // Set the current node to the top of the stack
                this->_node_stack.pop();
            } else {
                this->_current = nullptr; // No more nodes to visit
            }

            return *this;
        }

        bool operator!=(const BaseIterator<T>& other) const override { // Not equal operator
            return this->_current != static_cast<const BinaryInOrderIterator*>(&other)->_current;
        }

        Node<T>* operator*() const override { // Dereference operator
            return this->_current.get();
        }

        Node<T>* operator->() const override { // Member access operator
            return this->_current.get();
        }
    };

    // Post-Order Iterator (Binary Tree)
    class BinaryPostOrderIterator : public BinaryTreeIterator<T> {
    public:
        BinaryPostOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                traverse_post_order(root); // Traverse in post-order
                if (!this->_node_stack.empty()) {
                    this->_current = this->_node_stack.top(); // Set the current node to the top of the stack
                    this->_node_stack.pop();
                }
            }
        }

        BinaryPostOrderIterator& operator++() override { // Post-order increment operator
            if (!this->_current) return *this;

            if (!this->_node_stack.empty()) {
                this->_current = this->_node_stack.top(); // Set the current node to the top of the stack
                this->_node_stack.pop();
            } else {
                this->_current = nullptr; // No more nodes to visit
            }

            return *this;
        }

        bool operator!=(const BaseIterator<T>& other) const override { // Not equal operator
            return this->_current != static_cast<const BinaryPostOrderIterator*>(&other)->_current;
        }

        Node<T>* operator*() const override { // Dereference operator
            return this->_current.get();
        }

        Node<T>* operator->() const override { // Member access operator
            return this->_current.get();
        }

    private:
        void traverse_post_order(std::shared_ptr<Node<T>> node) { // Helper function for post-order traversal
            std::stack<std::shared_ptr<Node<T>>> temp_stack;
            temp_stack.push(node);

            while (!temp_stack.empty()) {
                auto current = temp_stack.top(); // Get the top node
                temp_stack.pop();
                this->_node_stack.push(current); // Push the node to the stack

                for (const auto& child : current->children) {
                    temp_stack.push(child); // Push the children
                }
            }
        }
    };

    // DFS Iterator (K-ary Tree)
    class DFSIterator : public BaseIterator<T> {
    private:
        std::stack<std::shared_ptr<Node<T>>> nodes; // Stack for DFS
    public:
        DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) nodes.push(root);
            if (!nodes.empty()) {
                this->_current = nodes.top(); // Set the current node to the top of the stack
                nodes.pop();
            }
        }

        DFSIterator& operator++() override { // DFS increment operator
            if (this->_current == nullptr) {
                return *this;
            }

            for (auto it = this->_current->children.rbegin(); it != this->_current->children.rend(); ++it) {
                nodes.push(*it); // Push the children in reverse order
            }

            if (!nodes.empty()) {
                this->_current = nodes.top(); // Set the current node to the top of the stack
                nodes.pop();
            } else {
                this->_current = nullptr; // No more nodes to visit
            }

            return *this;
        }

        bool operator!=(const BaseIterator<T>& other) const override { // Not equal operator
            return this->_current != static_cast<const DFSIterator*>(&other)->_current;
        }

        Node<T>* operator*() const override { // Dereference operator
            return this->_current.get();
        }

        Node<T>* operator->() const override { // Member access operator
            return this->_current.get();
        }
    };

    // BFS Iterator
    class BFSIterator : public BaseIterator<T> {
    private:
        std::queue<std::shared_ptr<Node<T>>> nodes; // Queue for BFS
    public:
        BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) nodes.push(root);
            if (!nodes.empty()) {
                this->_current = nodes.front(); // Set the current node to the front of the queue
                nodes.pop();
            }
        }

        BFSIterator& operator++() override { // BFS increment operator
            if (this->_current == nullptr) {
                return *this;
            }

            for (const auto& child : this->_current->children) {
                nodes.push(child); // Enqueue the children
            }

            if (!nodes.empty()) {
                this->_current = nodes.front(); // Set the current node to the front of the queue
                nodes.pop();
            } else {
                this->_current = nullptr; // No more nodes to visit
            }

            return *this;
        }

        bool operator!=(const BaseIterator<T>& other) const override { // Not equal operator
            return this->_current != static_cast<const BFSIterator*>(&other)->_current;
        }

        Node<T>* operator*() const override { // Dereference operator
            return this->_current.get();
        }

        Node<T>* operator->() const override { // Member access operator
            return this->_current.get();
        }
    };

    // Functions to get the beginning and end iterators for various traversal methods
    BinaryPreOrderIterator begin_pre_order() const {
        return BinaryPreOrderIterator(root);
    }

    BinaryPreOrderIterator end_pre_order() const {
        return BinaryPreOrderIterator(nullptr);
    }

    BinaryInOrderIterator begin_in_order() const {
        return BinaryInOrderIterator(root);
    }

    BinaryInOrderIterator end_in_order() const {
        return BinaryInOrderIterator(nullptr);
    }

    BinaryPostOrderIterator begin_post_order() const {
        return BinaryPostOrderIterator(root);
    }

    BinaryPostOrderIterator end_post_order() const {
        return BinaryPostOrderIterator(nullptr);
    }

    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }
};
