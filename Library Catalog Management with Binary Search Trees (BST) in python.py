class Node:
    def __init__(self, isbn, book_data):
        self.isbn = isbn
        self.book_data = book_data
        self.left = None
        self.right = None


class BST:
    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        if not self.root:
            self.root = Node(isbn, book_data)
        else:
            self._insert(self.root, isbn, book_data)

    def _insert(self, node, isbn, book_data):
        if isbn < node.isbn:
            if node.left is None:
                node.left = Node(isbn, book_data)
            else:
                self._insert(node.left, isbn, book_data)
        elif isbn > node.isbn:
            if node.right is None:
                node.right = Node(isbn, book_data)
            else:
                self._insert(node.right, isbn, book_data)

    def search(self, isbn):
        return self._search(self.root, isbn)

    def _search(self, node, isbn):
        if node is None:
            return None
        if isbn == node.isbn:
            return node.book_data
        elif isbn < node.isbn:
            return self._search(node.left, isbn)
        else:
            return self._search(node.right, isbn)

    def delete(self, isbn):
        self.root = self._delete(self.root, isbn)

    def _delete(self, node, isbn):
        if node is None:
            return node
        if isbn < node.isbn:
            node.left = self._delete(node.left, isbn)
        elif isbn > node.isbn:
            node.right = self._delete(node.right, isbn)
        else:
            # Node to delete found
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                # Node with two children: get the inorder successor (smallest in the right subtree)
                min_larger_node = self._get_min(node.right)
                node.isbn = min_larger_node.isbn
                node.book_data = min_larger_node.book_data
                node.right = self._delete(node.right, min_larger_node.isbn)
        return node

    def _get_min(self, node):
        while node.left is not None:
            node = node.left
        return node

# Example usage
if __name__ == "__main__":
    bst = BST()
    bst.insert("978-3-16-148410-0", {"title": "Book A", "author": "Author A"})
    bst.insert("978-1-23-456789-7", {"title": "Book B", "author": "Author B"})
    
    print(bst.search("978-3-16-148410-0"))  # Output: {'title': 'Book A', 'author': 'Author A'}
    
    bst.delete("978-3-16-148410-0")
    print(bst.search("978-3-16-148410-0"))  # Output: None
