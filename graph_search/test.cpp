#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>

using namespace std;

TEST_CASE("Binary Tree Traversals") {
    Node<double> root_node(1.0);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(2.0);
    Node<double> n2(3.0);
    Node<double> n3(4.0);
    Node<double> n4(5.0);
    Node<double> n5(6.0);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    SUBCASE("Pre-Order Traversal") {
        vector<double> expected = {1.0, 2.0, 4.0, 5.0, 3.0, 6.0};
        auto it = tree.begin_pre_order();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("In-Order Traversal") {
        vector<double> expected = {4.0, 2.0, 5.0, 1.0, 6.0, 3.0};
        auto it = tree.begin_in_order();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("Post-Order Traversal") {
        vector<double> expected = {4.0, 5.0, 2.0, 6.0, 3.0, 1.0};
        auto it = tree.begin_post_order();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("BFS Traversal") {
        vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        auto it = tree.begin_bfs_scan();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("DFS Traversal") {
        vector<double> expected = {1.0, 2.0, 4.0, 5.0, 3.0, 6.0};
        auto it = tree.begin_dfs_scan();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("Adding to non-existing node") {
        Node<double> non_existing_node(99.0);
        Node<double> new_node(100.0);
        CHECK_THROWS(tree.add_sub_node(non_existing_node, new_node));
    }

    SUBCASE("Adding more than 2 children to root in binary tree") {
        Node<double> extra_node(7.0);
        tree.add_sub_node(root_node, extra_node);
        auto children = tree.get_root()->children;
        CHECK(children.size() == 2); // Should not add more than 2 children
    }



    SUBCASE("Adding a node with children to binary tree") {
        Node<double> complex_node(10.0);
        Node<double> complex_child1(11.0);
        Node<double> complex_child2(12.0);

        Tree<double> complex_tree;
        complex_tree.add_root(complex_node);
        complex_tree.add_sub_node(complex_node, complex_child1);
        complex_tree.add_sub_node(complex_node, complex_child2);

        CHECK_NOTHROW(tree.add_sub_node(root_node, complex_node)); // Should not throw but maintain binary tree properties
        auto children = tree.get_root()->children;
        CHECK(children.size() == 2); // Should still maintain the binary tree structure
    }
}

TEST_CASE("3-Ary Tree Traversals") {
    Node<double> root_node(1.0);
    Tree<double, 3> tree;
    tree.add_root(root_node);
    Node<double> n1(2.0);
    Node<double> n2(3.0);
    Node<double> n3(4.0);
    Node<double> n4(5.0);
    Node<double> n5(6.0);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);

    SUBCASE("DFS Traversal") {
        vector<double> expected = {1.0, 2.0, 5.0, 6.0, 3.0, 4.0};
        auto it = tree.begin_dfs_scan();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("BFS Traversal") {
        vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        auto it = tree.begin_bfs_scan();
        for (double val : expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("Adding more than 3 children to root in 3-ary tree") {
        Node<double> extra_node(7.0);
        tree.add_sub_node(root_node, extra_node);
        auto children = tree.get_root()->children;
        CHECK(children.size() == 3); // Should not add more than 3 children
    }
}

TEST_CASE("Min-Heap Conversion") {
    Node<double> root_node(5.0);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(3.0);
    Node<double> n2(8.0);
    Node<double> n3(1.0);
    Node<double> n4(4.0);
    Node<double> n5(7.0);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    tree.myHeap();
    vector<double> expected = {1.0, 3.0, 4.0, 5.0, 7.0, 8.0};
    auto it = tree.begin_bfs_scan();
    for (double val : expected) {
        CHECK((*it)->get_value() == val);
        ++it;
    }
}

TEST_CASE("Binary Tree with Complex Numbers") {
    Node<Complex> root_node(Complex(1.0, 1.0));
    Tree<Complex> tree;
    tree.add_root(root_node);
    Node<Complex> c1(Complex(2.0, 2.0));
    Node<Complex> c2(Complex(3.0, 3.0));
    Node<Complex> c3(Complex(4.0, 4.0));
    Node<Complex> c4(Complex(5.0, 5.0));
    Node<Complex> c5(Complex(6.0, 6.0));

    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(c1, c3);
    tree.add_sub_node(c1, c4);
    tree.add_sub_node(c2, c5);

    SUBCASE("Pre-Order Traversal") {
        vector<Complex> expected = {Complex(1.0, 1.0), Complex(2.0, 2.0), Complex(4.0, 4.0), Complex(5.0, 5.0),
                                    Complex(3.0, 3.0), Complex(6.0, 6.0)};
        auto it = tree.begin_pre_order();
        for (Complex val: expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("In-Order Traversal") {
        vector<Complex> expected = {Complex(4.0, 4.0), Complex(2.0, 2.0), Complex(5.0, 5.0), Complex(1.0, 1.0),
                                    Complex(6.0, 6.0), Complex(3.0, 3.0)};
        auto it = tree.begin_in_order();
        for (Complex val: expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("Post-Order Traversal") {
        vector<Complex> expected = {Complex(4.0, 4.0), Complex(5.0, 5.0), Complex(2.0, 2.0), Complex(6.0, 6.0),
                                    Complex(3.0, 3.0), Complex(1.0, 1.0)};
        auto it = tree.begin_post_order();
        for (Complex val: expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("BFS Traversal") {
        vector<Complex> expected = {Complex(1.0, 1.0), Complex(2.0, 2.0), Complex(3.0, 3.0), Complex(4.0, 4.0),
                                    Complex(5.0, 5.0), Complex(6.0, 6.0)};
        auto it = tree.begin_bfs_scan();
        for (Complex val: expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

    SUBCASE("DFS Traversal") {
        vector<Complex> expected = {Complex(1.0, 1.0), Complex(2.0, 2.0), Complex(4.0, 4.0), Complex(5.0, 5.0),
                                    Complex(3.0, 3.0), Complex(6.0, 6.0)};
        auto it = tree.begin_dfs_scan();
        for (Complex val: expected) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }
// Additional test for Min-Heap with Complex numbers
    SUBCASE("Min-Heap with Complex Numbers") {
        Node<Complex> root_node(Complex(3.4, 5.2));
        Tree<Complex> tree;
        tree.add_root(root_node);
        Node<Complex> c1(Complex(7.1, 8.3));
        Node<Complex> c2(Complex(1.2, 3.4));
        Node<Complex> c3(Complex(2.9, 4.1));
        Node<Complex> c4(Complex(5.6, 1.1));
        Node<Complex> c5(Complex(2.5, 9.8));

        tree.add_sub_node(root_node, c1);
        tree.add_sub_node(root_node, c2);
        tree.add_sub_node(c1, c3);
        tree.add_sub_node(c1, c4);
        tree.add_sub_node(c2, c5);

        tree.myHeap();

        // Corrected expected heap order based on magnitude
        vector<Complex> expected_heap = {
                Complex(1.2, 3.4), // Magnitude: sqrt(1.2^2 + 3.4^2) = 3.57
                Complex(2.9, 4.1), // Magnitude: sqrt(2.9^2 + 4.1^2) = 5.06
                Complex(5.6, 1.1), // Magnitude: sqrt(5.6^2 + 1.1^2) = 5.70
                Complex(3.4, 5.2), // Magnitude: sqrt(3.4^2 + 5.2^2) = 6.25
                Complex(2.5, 9.8), // Magnitude: sqrt(2.5^2 + 9.8^2) = 10.13
                Complex(7.1, 8.3)  // Magnitude: sqrt(7.1^2 + 8.3^2) = 10.92
        };

        auto it = tree.begin_bfs_scan();
        for (Complex val : expected_heap) {
            CHECK((*it)->get_value() == val);
            ++it;
        }
    }

}

