class BTreeNode:
    def __init__(self, t, leaf=False):
        self.t = t  # Minimum degree
        self.leaf = leaf  # True if leaf node
        self.keys = []  # List of keys in the node
        self.children = []  # List of child nodes

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(t, True)
        self.t = t  # Minimum degree

    def insert(self, file_name, location):
        root = self.root
        if len(root.keys) == (2 * self.t) - 1:  # If root is full
            new_node = BTreeNode(self.t, False)
            new_node.children.append(self.root)
            self.split_child(new_node, 0)
            self.root = new_node
            self.insert_non_full(new_node, file_name, location)
        else:
            self.insert_non_full(root, file_name, location)

    def insert_non_full(self, node, file_name, location):
        i = len(node.keys) - 1
        if node.leaf:
            # Insert file_name in leaf node
            node.keys.append((file_name, location))
            node.keys.sort()  # Sort keys after insertion
        else:
            while i >= 0 and file_name < node.keys[i][0]:
                i -= 1
            i += 1
            if len(node.children[i].keys) == (2 * self.t) - 1:
                self.split_child(node, i)
                if file_name > node.keys[i][0]:
                    i += 1
            self.insert_non_full(node.children[i], file_name, location)

    def split_child(self, parent, i):
        t = parent.t
        new_node = BTreeNode(t, parent.children[i].leaf)
        child = parent.children[i]
        new_node.keys = child.keys[t - 1:]  # New node gets half of the keys
        child.keys = child.keys[:t - 1]  # Parent keeps the first half
        if not child.leaf:
            new_node.children = child.children[t:]  # Transfer children to new node
            child.children = child.children[:t]
        parent.children.insert(i + 1, new_node)  # Insert new node to parent
        parent.keys.insert(i, child.keys[-1])  # Insert the middle key in the parent

    def search(self, file_name):
        return self.search_helper(self.root, file_name)

    def search_helper(self, node, file_name):
        i = 0
        while i < len(node.keys) and file_name > node.keys[i][0]:
            i += 1
        if i < len(node.keys) and file_name == node.keys[i][0]:
            return node.keys[i][1]  # Return the location if found
        if node.leaf:
            return None  # Not found in a leaf node
        return self.search_helper(node.children[i], file_name)

# Example usage
if __name__ == "__main__":
    btree = BTree(2)  # Minimum degree t = 2
    btree.insert("file1.txt", "/path/to/file1.txt")
    btree.insert("file2.txt", "/path/to/file2.txt")
    location = btree.search("file1.txt")
    print(f"Location of file1.txt: {location}")
