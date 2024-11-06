#include <iostream>
#include <vector>

class DisjointSetUnion {
public:
    DisjointSetUnion(int size);
    int find(int item);
    void union_sets(int item1, int item2);
    bool connected(int item1, int item2);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

DisjointSetUnion::DisjointSetUnion(int size) {
    parent.resize(size);
    rank.resize(size, 0);
    for (int i = 0; i < size; ++i) {
        parent[i] = i;  // Each element is its own parent initially
    }
}

int DisjointSetUnion::find(int item) {
    if (parent[item] != item) {
        parent[item] = find(parent[item]);  // Path compression
    }
    return parent[item];
}

void DisjointSetUnion::union_sets(int item1, int item2) {
    int root1 = find(item1);
    int root2 = find(item2);

    if (root1 != root2) {
        // Union by rank
        if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else {
            parent[root2] = root1;
            rank[root1]++;
        }
    }
}

bool DisjointSetUnion::connected(int item1, int item2) {
    return find(item1) == find(item2);
}

// Example usage
int main() {
    int n = 10;  // Number of computers
    DisjointSetUnion dsu(n);

    // Connect computers
    dsu.union_sets(0, 1);
    dsu.union_sets(1, 2);
    dsu.union_sets(3, 4);

    // Check connections
    std::cout << std::boolalpha;
    std::cout << "Connected(0, 2): " << dsu.connected(0, 2) << "\n";  // Should print true
    std::cout << "Connected(0, 3): " << dsu.connected(0, 3) << "\n";  // Should print false
    dsu.union_sets(2, 3);
    std::cout << "Connected(0, 3): " << dsu.connected(0, 3) << "\n";  // Should print true

    return 0;
}
