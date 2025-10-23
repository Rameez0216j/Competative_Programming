// Video : https://www.youtube.com/watch?v=KxLtIrCyXwE
/*
All important code parts and what they represent.
-------------------------------------------------
Edge --> represents a connection between two vertices with a given weight
edges --> list of all edges in the graph
parent[] --> used by Disjoint Set Union (DSU) to track parent of each vertex
rank[] --> helps keep tree shallow in DSU (Union by Rank optimization)
findParent() --> returns the ultimate parent (representative) of a vertex
unionByRank() --> merges two sets (components) using rank to optimize
*/

/*
Proper intuitive code with better naming convention
---------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge (u, v, weight)
struct Edge {
    int source;
    int destination;
    int weight;
};

// Comparator to sort edges by weight
bool compareByWeight(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int size) {
        parent.resize(size + 1);
        rank.resize(size + 1, 0);
        for (int i = 0; i <= size; ++i)
            parent[i] = i;
    }

    int findParent(int node) {
        // Path Compression Optimization
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v) {
        int parentU = findParent(u);
        int parentV = findParent(v);

        if (parentU == parentV)
            return;

        // Attach smaller rank tree under the higher rank tree
        if (rank[parentU] < rank[parentV])
            parent[parentU] = parentV;
        else if (rank[parentV] < rank[parentU])
            parent[parentV] = parentU;
        else {
            parent[parentV] = parentU;
            rank[parentU]++;
        }
    }
};

int main() {
    int totalVertices, totalEdges;
    cin >> totalVertices >> totalEdges;

    vector<Edge> edges(totalEdges);
    for (int i = 0; i < totalEdges; ++i) {
        cin >> edges[i].source >> edges[i].destination >> edges[i].weight;
    }

    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end(), compareByWeight);

    DisjointSet dsu(totalVertices);

    int totalMSTCost = 0;
    vector<Edge> mstEdges;  // store the edges of MST

    // Step 2: Iterate over all edges in sorted order
    for (auto &edge : edges) {
        int parentU = dsu.findParent(edge.source);
        int parentV = dsu.findParent(edge.destination);

        // Step 3: Include edge only if it doesn’t form a cycle
        if (parentU != parentV) {
            totalMSTCost += edge.weight;
            mstEdges.push_back(edge);
            dsu.unionByRank(parentU, parentV);
        }
    }

    // Step 4: Print MST result
    cout << "Edges in MST:\n";
    for (auto &edge : mstEdges) {
        cout << edge.source << " - " << edge.destination 
             << "  (Cost: " << edge.weight << ")\n";
    }
    cout << "Total Minimum Cost = " << totalMSTCost << endl;

    return 0;
}

/*
Tips and Tricks & Pattern Recognition
-------------------------------------

🔹 Pattern Recognition:
   - You are given a list of **edges** (not adjacency list).
   - Problem says “connect all points/nodes with minimum cost”.
   - Graph is **undirected and weighted**.
   - It often says “find minimum cost to connect all components”.
   - Kruskal’s is chosen when edges are explicitly given and graph is sparse.

🔹 Why DSU is used:
   - To check if adding an edge will create a cycle.
   - DSU efficiently groups nodes into connected components.

🔹 Time Complexity:
   - Sorting edges: O(E log E)
   - DSU operations: ~O(E α(V)) (α(V) is very slow-growing inverse Ackermann function)
   - Total: O(E log E)

🔹 Space Complexity:
   - O(V + E)

🔹 When to Prefer Kruskal over Prim:
   - Graph is **sparse** (fewer edges).
   - Edges are already given in a list format.
   - You only need the MST cost, not necessarily adjacency connections.

🔹 Common Pitfalls:
   - Forgetting to use path compression in DSU (causes TLE on large inputs).
   - Not handling disconnected graphs (Kruskal will stop early).

🔹 Optimizations:
   - Use `union by rank` + `path compression`.
   - If you only need MST weight, you don’t need to store parent edges.
*/
