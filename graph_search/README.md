# Binary Tree and K-Ary Tree Implementation

This project implements a generic Binary Tree and K-Ary Tree in C++. The project includes:
1. Pre-order, In-order, and Post-order traversals for binary trees.
2. Breadth-First Search (BFS) and Depth-First Search (DFS) traversals for both binary and k-ary trees.
3. Min-Heap conversion for binary trees.
4. Handling of complex numbers in tree nodes.
5. Visualization of trees using SFML.

## Project Structure

- **Node.hpp**: Defines the `Node` class, representing nodes in the tree.
- **Tree.hpp**: Implements the `Tree` class with various traversal methods and min-heap conversion.
- **Complex.hpp**: Defines the `Complex` class to handle complex numbers as node values.
- **demo.cpp**: Demonstrates the usage of the tree classes, including visualization with SFML.
- **test.cpp**: Contains test cases to validate the functionality of the tree classes using the doctest framework.
- **doctest.h**: The doctest framework header for unit testing.
- **makefile**: Makefile to compile and run the demo and test programs.

## Functions and Algorithms

### Node Class

The `Node` class represents a node in the tree. Each node contains:
- `data`: The value of the node.
- `children`: A vector of shared pointers to its children.

### Tree Class

The `Tree` class represents the tree structure and includes various methods for traversal and manipulation:
- **Traversal Methods**:
    - `begin_pre_order()`, `end_pre_order()`: Pre-order traversal for binary trees.
    - `begin_in_order()`, `end_in_order()`: In-order traversal for binary trees.
    - `begin_post_order()`, `end_post_order()`: Post-order traversal for binary trees.
    - `begin_bfs_scan()`, `end_bfs_scan()`: BFS traversal for both binary and k-ary trees.
    - `begin_dfs_scan()`, `end_dfs_scan()`: DFS traversal for both binary and k-ary trees.
- **Min-Heap Conversion**:
    - `myHeap()`: Converts the binary tree into a min-heap using standard algorithms.

### Complex Class

The `Complex` class represents complex numbers with real and imaginary parts and includes:
- Overloaded operators for addition, comparison, and output.

### GUI with SFML

The project includes a graphical visualization of trees using the SFML library:
- Nodes are represented as circles with their values displayed.
- Edges are represented as lines connecting parent and child nodes.

## Libraries Used

- **SFML**: Used for graphical visualization.
- **doctest**: Used for unit testing.

## Compilation and Execution

### Compiling the Demo

To compile the all of the program, use the following command:

```sh
make
```
This command will compile demo.cpp and generate an executable demo.

Running the Demo(Main)
To run the demo program, use the following command:
```sh
make tree
```

Compiling the Tests
To compile the tests, use the following command:
```sh
make test
```
This command will compile test.cpp and generate an executable test.


Running the Tests
To run the tests, use the following command:
```sh
./test
```
Check for Memory Leaks with Valgrind
To check for memory leaks using Valgrind:
```sh
make valgrind
```

Cleaning the Build
To clean the build files, use the following command:
```sh
make clean
```