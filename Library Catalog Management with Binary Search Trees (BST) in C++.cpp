#include <iostream>
#include <unordered_map>
#include <string>

struct Node {
    std::string isbn;
    std::unordered_map<std::string, std::string> book_data;
    Node* left;
    Node* right;

    Node(const std::string& isbn, const std::unordered_map<std::string, std::string>& data)
        : isbn(isbn), book_data(data), left(nullptr), right(nullptr) {}
};

class BookBST {
private:
    Node* root;

    Node* insert(Node* node, const std::string& isbn, const std::unordered_map<std::string, std::string>& book_data) {
        if (!node) {
            return new Node(isbn, book_data);
        }

        if (isbn < node->isbn) {
            node->left = insert(node->left, isbn, book_data);
        } else if (isbn > node->isbn) {
            node->right = insert(node->right, isbn, book_data);
        }

        return node;
    }

    Node* search(Node* node, const std::string& isbn) {
        if (!node || node->isbn == isbn) {
            return node;
        }

        if (isbn < node->isbn) {
            return search(node->left, isbn);
        }
        return search(node->right, isbn);
    }

    Node* deleteNode(Node* node, const std::string& isbn) {
        if (!node) return node;

        if (isbn < node->isbn) {
            node->left = deleteNode(node->left, isbn);
        } else if (isbn > node->isbn) {
            node->right = deleteNode(node->right, isbn);
        } else {
            // Node with only one child or no child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* minLargerNode = node->right;
            while (minLargerNode && minLargerNode->left) {
                minLargerNode = minLargerNode->left;
            }

            // Copy the inorder successor's content to this node
            node->isbn = minLargerNode->isbn;
            node->book_data = minLargerNode->book_data; // Fix here

            // Delete the inorder successor
            node->right = deleteNode(node->right, minLargerNode->isbn);
        }
        return node;
    }

public:
    BookBST() : root(nullptr) {}

    void insert(const std::string& isbn, const std::unordered_map<std::string, std::string>& book_data) {
        root = insert(root, isbn, book_data);
    }

    std::unordered_map<std::string, std::string> search(const std::string& isbn) {
        Node* result = search(root, isbn);
        return result ? result->book_data : std::unordered_map<std::string, std::string>{};
    }

    void deleteNode(const std::string& isbn) {
        root = deleteNode(root, isbn);
    }
};

int main() {
    BookBST bst;
    
    bst.insert("978-3-16-148410-0", {{"title", "Book A"}, {"author", "Author A"}});
    bst.insert("978-1-23-456789-7", {{"title", "Book B"}, {"author", "Author B"}});

    auto bookData = bst.search("978-3-16-148410-0");
    for (const auto& pair : bookData) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    bst.deleteNode("978-3-16-148410-0");
    bookData = bst.search("978-3-16-148410-0");
    if (bookData.empty()) {
        std::cout << "Book not found." << std::endl;
    }

    return 0;
}
