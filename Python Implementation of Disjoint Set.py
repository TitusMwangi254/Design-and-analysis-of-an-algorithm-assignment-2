class DisjointSet:
    def __init__(self, size):
        # Initialize the parent array and rank array
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, item):
        # Path compression
        if self.parent[item] != item:
            self.parent[item] = self.find(self.parent[item])
        return self.parent[item]

    def union(self, item1, item2):
        root1 = self.find(item1)
        root2 = self.find(item2)

        if root1 != root2:
            # Union by rank
            if self.rank[root1] > self.rank[root2]:
                self.parent[root2] = root1
            elif self.rank[root1] < self.rank[root2]:
                self.parent[root1] = root2
            else:
                self.parent[root2] = root1
                self.rank[root1] += 1

    def connected(self, item1, item2):
        return self.find(item1) == self.find(item2)

# Example usage
if __name__ == "__main__":
    n = 10  # Number of computers
    ds = DisjointSet(n)

    # Connect computers
    ds.union(0, 1)
    ds.union(1, 2)
    ds.union(3, 4)

    # Check connections
    print(ds.connected(0, 2))  # Should print True
    print(ds.connected(0, 3))  # Should print False
    ds.union(2, 3)
    print(ds.connected(0, 3))  # Should print True
