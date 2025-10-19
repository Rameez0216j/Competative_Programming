/*
Disjoint Set Union (Union-Find)
--------------------------------
Operations:
1. findParent(x)  → returns representative (leader) of set containing x
2. unionSets(x,y) → merges two sets if they are not already connected
*/

#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion {
private:
    vector<int> parent;  // parent[i] → parent (leader) of node i
    vector<int> size;    // size[i] → size of the set whose leader is i

public:
    // Constructor: initialize n elements, each as its own set
    DisjointSetUnion(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i; // every node is its own parent initially
    }

    // Find with path compression
    int findParent(int node) {
        if (node == parent[node])
            return node; // node is its own parent (leader)
        // Path compression: directly attach node to its ultimate parent
        return parent[node] = findParent(parent[node]);
    }

    // Union by size
    void unionSets(int a, int b) {
        int rootA = findParent(a);
        int rootB = findParent(b);
        if (rootA == rootB)
            return; // already in the same set

        // attach smaller tree under the larger one
        if (size[rootA] < size[rootB])
            swap(rootA, rootB);

        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }

    // Check if two nodes are in the same set
    bool isConnected(int a, int b) {
        return findParent(a) == findParent(b);
    }
};

int main() {
    int n = 7;
    DisjointSetUnion dsu(n);

    dsu.unionSets(1, 2);
    dsu.unionSets(2, 3);
    dsu.unionSets(4, 5);

    cout << boolalpha;
    cout << "Are 1 and 3 connected? " << dsu.isConnected(1, 3) << "\n"; // true
    cout << "Are 3 and 4 connected? " << dsu.isConnected(3, 4) << "\n"; // false

    dsu.unionSets(3, 4);
    cout << "After union(3,4): Are 1 and 5 connected? " << dsu.isConnected(1, 5) << "\n"; // true
}
