#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <limits>

class Node {
public:
    std::string key;  // Node identifier (e.g., location)
    int value;  // Distance or priority value
    int degree;  // Number of children
    Node* parent;  // Pointer to parent node
    Node* child;   // Pointer to first child node
    bool is_marked;  // True if node was cut from parent
    Node* next;  // Pointer to next node in circular list
    Node* prev;  // Pointer to previous node in circular list

    Node(std::string k, int v) : key(k), value(v), degree(0), parent(nullptr), child(nullptr),
                                  is_marked(false), next(this), prev(this) {}
};

class FibHeap {
private:
    Node* min_node;  // Node with the minimum key
    int num_nodes;   // Total number of nodes in the heap

public:
    FibHeap() : min_node(nullptr), num_nodes(0) {}

    void insert(const std::string& key, int value);
    std::pair<std::string, int> extract_min();
    void decrease_key(Node* node, int new_value);

private:
    void _link(Node* min_node, Node* new_node);
    void _consolidate();
    void _cut(Node* node, Node* parent);
};

void FibHeap::insert(const std::string& key, int value) {
    Node* new_node = new Node(key, value);
    if (min_node == nullptr) {
        min_node = new_node;
    } else {
        _link(min_node, new_node);
        if (new_node->value < min_node->value) {
            min_node = new_node;
        }
    }
    num_nodes++;
}

void FibHeap::_link(Node* min_node, Node* new_node) {
    new_node->prev = min_node->prev;
    new_node->next = min_node;
    min_node->prev->next = new_node;
    min_node->prev = new_node;
}

std::pair<std::string, int> FibHeap::extract_min() {
    Node* min_node = this->min_node;
    if (min_node != nullptr) {
        if (min_node->child != nullptr) {
            Node* child = min_node->child;
            while (true) {
                Node* next_child = child->next;
                _link(this->min_node, child);
                child->parent = nullptr;
                child = next_child;
                if (child == min_node->child) break;
            }
        }
        min_node->prev->next = min_node->next;
        min_node->next->prev = min_node->prev;

        if (min_node == min_node->next) {
            this->min_node = nullptr;
        } else {
            this->min_node = min_node->next;
            _consolidate();
        }
        num_nodes--;
    }
    return {min_node->key, min_node->value};
}

void FibHeap::_consolidate() {
    int max_degree = static_cast<int>(std::sqrt(num_nodes)) + 1;
    std::vector<Node*> roots(max_degree, nullptr);
    Node* current = min_node;
    std::vector<Node*> nodes;

    do {
        nodes.push_back(current);
        current = current->next;
    } while (current != min_node);

    for (Node* node : nodes) {
        int degree = node->degree;
        while (roots[degree] != nullptr) {
            if (node->value > roots[degree]->value) {
                std::swap(node, roots[degree]);
            }
            _link(node, roots[degree]);
            roots[degree]->parent = node;
            roots[degree] = nullptr;
            degree++;
        }
        roots[degree] = node;
    }

    min_node = nullptr;
    for (Node* root : roots) {
        if (root != nullptr) {
            if (min_node == nullptr) {
                min_node = root;
            } else if (root->value < min_node->value) {
                min_node = root;
            }
        }
    }
}

void FibHeap::_cut(Node* node, Node* parent) {
    if (parent->child == node) {
        parent->child = node->next != node ? node->next : nullptr;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    parent->degree--;
    node->next = node->prev = node;
    node->parent = nullptr;
    node->is_marked = false;
}

void FibHeap::decrease_key(Node* node, int new_value) {
    if (new_value > node->value) {
        throw std::invalid_argument("New value is greater than current value");
    }
    node->value = new_value;
    Node* parent = node->parent;
    if (parent != nullptr && node->value < parent->value) {
        _cut(node, parent);
        _link(min_node, node);
    }
    if (node->value < min_node->value) {
        min_node = node;
    }
}

// Example usage of FibHeap
int main() {
    FibHeap fib_heap;
    fib_heap.insert("A", 10);
    fib_heap.insert("B", 5);
    fib_heap.insert("C", 15);

    auto min = fib_heap.extract_min();
    std::cout << "Extracted min: (" << min.first << ", " << min.second << ")\n"; // Should print ("B", 5)
    return 0;
}
