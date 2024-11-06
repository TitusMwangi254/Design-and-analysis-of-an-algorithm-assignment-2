#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class BTreeNode : public std::enable_shared_from_this<BTreeNode> {
public:
    int t;  // Minimum degree
    std::vector<std::pair<std::string, std::string>> keys;  // (file_name, location)
    std::vector<std::shared_ptr<BTreeNode>> children;  // Child pointers
    bool leaf;  // True if leaf node

    BTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf) {}

    void insertNonFull(const std::string& file_name, const std::string& location);
    void splitChild(int i, std::shared_ptr<BTreeNode> parent);
};

class BTree {
public:
    std::shared_ptr<BTreeNode> root;
    int t;  // Minimum degree

    BTree(int _t) : root(nullptr), t(_t) {}

    void insert(const std::string& file_name, const std::string& location);
    std::string search(const std::string& file_name);
    std::shared_ptr<BTreeNode> searchHelper(std::shared_ptr<BTreeNode> node, const std::string& file_name);
};

void BTreeNode::insertNonFull(const std::string& file_name, const std::string& location) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.emplace_back(file_name, location);
        std::sort(keys.begin(), keys.end());
    } else {
        while (i >= 0 && file_name < keys[i].first) {
            i--;
        }
        i++;
        if (children[i]->keys.size() == (2 * t) - 1) {
            splitChild(i, shared_from_this());
            if (file_name > keys[i].first) {
                i++;
            }
        }
        children[i]->insertNonFull(file_name, location);
    }
}

void BTreeNode::splitChild(int i, std::shared_ptr<BTreeNode> parent) {
    auto new_node = std::make_shared<BTreeNode>(t, leaf);
    auto child = children[i];
    new_node->keys.assign(child->keys.begin() + t - 1, child->keys.end());
    child->keys.resize(t - 1);
    if (!child->leaf) {
        new_node->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(t);
    }
    parent->children.insert(parent->children.begin() + i + 1, new_node);
    parent->keys.insert(parent->keys.begin() + i, child->keys.back());
}

void BTree::insert(const std::string& file_name, const std::string& location) {
    if (!root) {
        root = std::make_shared<BTreeNode>(t, true);
    }
    if (root->keys.size() == (2 * t) - 1) {
        auto new_root = std::make_shared<BTreeNode>(t, false);
        new_root->children.push_back(root);
        new_root->splitChild(0, new_root);
        root = new_root;
    }
    root->insertNonFull(file_name, location);
}

std::string BTree::search(const std::string& file_name) {
    auto result = searchHelper(root, file_name);
    return result ? result->keys[0].second : "";  // Return location if found
}

std::shared_ptr<BTreeNode> BTree::searchHelper(std::shared_ptr<BTreeNode> node, const std::string& file_name) {
    int i = 0;
    while (i < node->keys.size() && file_name > node->keys[i].first) {
        i++;
    }
    if (i < node->keys.size() && file_name == node->keys[i].first) {
        return node;  // Return the node if found
    }
    if (node->leaf) {
        return nullptr;  // Not found in a leaf node
    }
    return searchHelper(node->children[i], file_name);
}

// Example usage
int main() {
    BTree btree(2);  // Minimum degree t = 2
    btree.insert("file1.txt", "/path/to/file1.txt");
    btree.insert("file2.txt", "/path/to/file2.txt");
    std::string location = btree.search("file1.txt");
    std::cout << "Location of file1.txt: " << location << std::endl;
    return 0;
}
