class Node:
    def __init__(self, key, value):
        self.key = key  # Node identifier (e.g., location)
        self.value = value  # Distance or priority value
        self.degree = 0  # Number of children
        self.parent = None  # Pointer to parent node
        self.child = None  # Pointer to first child node
        self.is_marked = False  # True if node was cut from parent
        self.next = self  # Pointer to the next node in the circular list
        self.prev = self  # Pointer to the previous node in the circular list

class FibHeap:
    def __init__(self):
        self.min_node = None  # Node with the minimum key
        self.num_nodes = 0  # Total number of nodes in the heap

    def insert(self, key, value):
        new_node = Node(key, value)
        if self.min_node is None:
            self.min_node = new_node
        else:
            # Add new_node to the root list
            self._link(self.min_node, new_node)
            if new_node.value < self.min_node.value:
                self.min_node = new_node
        self.num_nodes += 1

    def _link(self, min_node, new_node):
        new_node.prev = min_node.prev
        new_node.next = min_node
        min_node.prev.next = new_node
        min_node.prev = new_node

    def extract_min(self):
        min_node = self.min_node
        if min_node is not None:
            if min_node.child is not None:
                # Add the children of min_node to the root list
                child = min_node.child
                while True:
                    next_child = child.next
                    self._link(self.min_node, child)
                    child.parent = None
                    child = next_child
                    if child == min_node.child:
                        break
            
            # Remove min_node from the root list
            min_node.prev.next = min_node.next
            min_node.next.prev = min_node.prev
            
            if min_node == min_node.next:  # Only node in the heap
                self.min_node = None
            else:
                self.min_node = min_node.next
                self._consolidate()
            
            self.num_nodes -= 1
        
        return min_node.key, min_node.value if min_node else None

    def _consolidate(self):
        max_degree = int(self.num_nodes ** 0.5) + 1
        roots = [None] * max_degree
        current = self.min_node
        nodes = []
        while True:
            nodes.append(current)
            current = current.next
            if current == self.min_node:
                break
        for node in nodes:
            degree = node.degree
            while roots[degree] is not None:
                if node.value > roots[degree].value:
                    node, roots[degree] = roots[degree], node
                self._link(node, roots[degree])
                roots[degree].parent = node
                roots[degree] = None
                degree += 1
            roots[degree] = node
        
        self.min_node = None
        for root in roots:
            if root is not None:
                if self.min_node is None:
                    self.min_node = root
                elif root.value < self.min_node.value:
                    self.min_node = root

    def decrease_key(self, node, new_value):
        if new_value > node.value:
            raise ValueError("New value is greater than current value")
        
        node.value = new_value
        parent = node.parent
        if parent is not None and node.value < parent.value:
            self._cut(node, parent)
            self._link(self.min_node, node)
        
        if node.value < self.min_node.value:
            self.min_node = node

    def _cut(self, node, parent):
        # Remove node from its parent's child list
        if parent.child == node:
            parent.child = node.next if node.next != node else None
        node.prev.next = node.next
        node.next.prev = node.prev
        parent.degree -= 1
        node.prev = node.next = node
        node.parent = None
        node.is_marked = False

# Example usage of FibHeap
if __name__ == "__main__":
    fib_heap = FibHeap()
    fib_heap.insert("A", 10)
    fib_heap.insert("B", 5)
    fib_heap.insert("C", 15)

    print(fib_heap.extract_min())  # Should print ('B', 5)
    fib_heap.decrease_key(fib_heap.min_node, 2)  # Assuming we have a reference to a node
    print(fib_heap.extract_min())  # Should print the updated min
