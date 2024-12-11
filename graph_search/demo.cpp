#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Tree.hpp"
#include <iostream>
#include "Complex.hpp"

using namespace std;

void drawNode(sf::RenderWindow& window, std::shared_ptr<Node<double>> node, float x, float y, float horizontalSpacing, float verticalSpacing);

int main() {
    // Create the first tree (binary tree)
    Node<double> root_node1 = Node<double>(1.1);
    Tree<double> tree1;
    tree1.add_root(root_node1);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree1.add_sub_node(root_node1, n1);
    tree1.add_sub_node(root_node1, n2);
    tree1.add_sub_node(n1, n3);
    tree1.add_sub_node(n1, n4);
    tree1.add_sub_node(n2, n5);

    // Create the second tree (3-ary tree)
    Node<double> root_node2 = Node<double>(2.1);
    Tree<double, 3> tree2;
    tree2.add_root(root_node2);
    Node<double> n6 = Node<double>(2.2);
    Node<double> n7 = Node<double>(2.3);
    Node<double> n8 = Node<double>(2.4);
    Node<double> n9 = Node<double>(2.5);
    Node<double> n10 = Node<double>(2.6);

    tree2.add_sub_node(root_node2, n6);
    tree2.add_sub_node(root_node2, n7);
    tree2.add_sub_node(root_node2, n8);
    tree2.add_sub_node(n6, n9);
    tree2.add_sub_node(n7, n10);

    // Create the third tree (binary tree for heap)
    Node<double> root_node3 = Node<double>(3.1);
    Tree<double> tree3;
    tree3.add_root(root_node3);
    Node<double> n11 = Node<double>(3.2);
    Node<double> n12 = Node<double>(3.3);
    Node<double> n13 = Node<double>(3.4);
    Node<double> n14 = Node<double>(3.5);
    Node<double> n15 = Node<double>(3.6);

    tree3.add_sub_node(root_node3, n11);
    tree3.add_sub_node(root_node3, n15);
    tree3.add_sub_node(n11, n13);
    tree3.add_sub_node(n11, n14);
    tree3.add_sub_node(n15, n12);

    // Create the fourth tree (binary tree with Complex values)
    Node<Complex> root_node4 = Node<Complex>(Complex(1.0, 1.0));
    Tree<Complex> tree4;
    tree4.add_root(root_node4);
    Node<Complex> c1 = Node<Complex>(Complex(2.0, 2.0));
    Node<Complex> c2 = Node<Complex>(Complex(3.0, 3.0));
    Node<Complex> c3 = Node<Complex>(Complex(4.0, 4.0));
    Node<Complex> c4 = Node<Complex>(Complex(5.0, 5.0));
    Node<Complex> c5 = Node<Complex>(Complex(6.0, 6.0));

    tree4.add_sub_node(root_node4, c1);
    tree4.add_sub_node(root_node4, c2);
    tree4.add_sub_node(c1, c3);
    tree4.add_sub_node(c1, c4);
    tree4.add_sub_node(c2, c5);


    // Print traversals for the binary tree
    cout << "Binary Tree Pre-Order:" << endl;
    for (auto it = tree1.begin_pre_order(); it != tree1.end_pre_order(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree Post-Order:" << endl;
    for (auto it = tree1.begin_post_order(); it != tree1.end_post_order(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree In-Order:" << endl;
    for (auto it = tree1.begin_in_order(); it != tree1.end_in_order(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree BFS:" << endl;
    for (auto it = tree1.begin_bfs_scan(); it != tree1.end_bfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree DFS:" << endl;
    for (auto it = tree1.begin_dfs_scan(); it != tree1.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    // Print traversals for the 3-ary tree
    cout << "3-Ary Tree Pre-Order (DFS):" << endl;
    for (auto it = tree2.begin_dfs_scan(); it != tree2.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "3-Ary Tree Post-Order (DFS):" << endl;
    for (auto it = tree2.begin_dfs_scan(); it != tree2.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "3-Ary Tree In-Order (DFS):" << endl;
    for (auto it = tree2.begin_dfs_scan(); it != tree2.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "3-Ary Tree BFS:" << endl;
    for (auto it = tree2.begin_bfs_scan(); it != tree2.end_bfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "3-Ary Tree DFS:" << endl;
    for (auto it = tree2.begin_dfs_scan(); it != tree2.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    // Convert binary tree to Min-Heap and print values
    cout << "Binary Tree Heap:" << endl;
    tree3.myHeap();
    for (auto it = tree3.begin_bfs_scan(); it != tree3.end_bfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }
  //  cout<<endl;
    cout << "Binary Tree In-Order (Complex):" << endl;
    for (auto it = tree4.begin_in_order(); it != tree4.end_in_order(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree BFS (Complex):" << endl;
    for (auto it = tree4.begin_bfs_scan(); it != tree4.end_bfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    cout << "Binary Tree DFS (Complex):" << endl;
    for (auto it = tree4.begin_dfs_scan(); it != tree4.end_dfs_scan(); ++it) {
        cout << (*it)->get_value() << endl;
    }

    // Create window with video mode and title
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Forest visualization");

    // to avoid the annoying warning:
    // Attempt to enable vertical sync
    try {
        window.setVerticalSyncEnabled(true);
        std::cout << "Vertical sync enabled" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Setting vertical sync not supported: " << e.what() << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Display the binary tree
        if (tree1.get_root()) {
            drawNode(window, tree1.get_root(), window.getSize().x / 6, 50, 100, 50);
        }

        // Display the 3-ary tree
        if (tree2.get_root()) {
            drawNode(window, tree2.get_root(), window.getSize().x / 2, 50, 100, 50);
        }

        // Display the binary heap tree
        if (tree3.get_root()) {
            drawNode(window, tree3.get_root(), 5 * window.getSize().x / 6, 50, 100, 50);
        }

        window.display();
    }

    return 0;
}

void drawNode(sf::RenderWindow& window, std::shared_ptr<Node<double>> node, float x, float y, float horizontalSpacing, float verticalSpacing) {
    // Calculate the position for children nodes
    float childX = x - (node->children.size() - 1) * horizontalSpacing / 2;
    for (auto& child : node->children) {
        // Draw a red line from the current node to the child node
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::Red),
                sf::Vertex(sf::Vector2f(childX, y + verticalSpacing), sf::Color::Red)
        };
        window.draw(line, 2, sf::Lines);

        // Recursively draw the child node
        drawNode(window, child, childX, y + verticalSpacing, horizontalSpacing / 2, verticalSpacing);
        childX += horizontalSpacing; // Update position for the next child
    }

    // Draw the node circle
    sf::CircleShape circle(15); // Circle with radius 15
    circle.setFillColor(sf::Color::White); // White fill color
    circle.setOutlineColor(sf::Color::Black); // Black outline color
    circle.setOutlineThickness(1); // Outline thickness
    circle.setPosition(x - 15, y - 15); // Position circle centered on (x, y)

    // Load font for the node value
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Draw the node value text
    sf::Text text;
    text.setFont(font); // Set font
    text.setString(std::to_string(node->get_value())); // Set text to node value
    text.setCharacterSize(12); // Character size
    text.setFillColor(sf::Color::Black); // Text color
    text.setPosition(x - 10, y - 10); // Position text centered on (x, y)

    // Draw the circle and text
    window.draw(circle);
    window.draw(text);
}
