// Video : https://www.youtube.com/watch?v=rnYBi9N_vw4

/*
All important code parts and what they represent.
-------------------------------------------------
adjList[u] --> stores pairs (v, weight) representing an edge u -> v with cost 'weight'
minHeap --> a priority queue that always gives the edge with the smallest weight
inMST[v] --> true if vertex 'v' is already included in the MST
parent[v] --> stores the vertex through which 'v' was connected in MST
key[v] --> stores the minimum weight edge that can connect 'v' to MST
*/

/*
Proper intuitive code with better naming convention
---------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int vertex;
    int weight;
};

int main() {
    int totalVertices, totalEdges;
    cin >> totalVertices >> totalEdges;

    // Build the adjacency list
    vector<vector<Edge>> adjList(totalVertices + 1);

    for (int i = 0; i < totalEdges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});  // Because the graph is undirected
    }

    // Initialize arrays
    vector<int> key(totalVertices + 1, INT_MAX);     // Smallest edge weight to connect vertex
    vector<int> parent(totalVertices + 1, -1);       // Parent in MST
    vector<bool> inMST(totalVertices + 1, false);    // Is vertex included in MST?

    // Min-heap: {weight, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    // Start from vertex 1 (you can start from any)
    key[1] = 0;
    minHeap.push({0, 1});  // weight, vertex

    while (!minHeap.empty()) {
        int currentVertex = minHeap.top().second;
        minHeap.pop();

        if (inMST[currentVertex]) continue;  // Skip if already included

        inMST[currentVertex] = true;  // Include in MST

        // Explore adjacent vertices
        for (auto &edge : adjList[currentVertex]) {
            int adjacentVertex = edge.vertex;
            int edgeWeight = edge.weight;

            // If adjacent vertex is not in MST and edge weight is smaller than its current key
            if (!inMST[adjacentVertex] && edgeWeight < key[adjacentVertex]) {
                key[adjacentVertex] = edgeWeight;
                parent[adjacentVertex] = currentVertex;
                minHeap.push({edgeWeight, adjacentVertex});
            }
        }
    }

    // Output the MST
    int totalCost = 0;
    cout << "Edges in MST:\n";
    for (int i = 2; i <= totalVertices; ++i) {
        cout << parent[i] << " - " << i << "  (Cost: " << key[i] << ")\n";
        totalCost += key[i];
    }

    cout << "Total Minimum Cost = " << totalCost << endl;
    return 0;
}

/*
Tips and Tricks & Pattern Recognition
-------------------------------------

🔹 Pattern Recognition:
   - The problem involves connecting all nodes with the minimum total cost (like cities, servers, or computers).
   - The graph is **undirected and weighted**.
   - It often says “connect all with minimum total cost” or “minimum wiring/cabling cost”.
   - No mention of paths between specific nodes — the goal is global connectivity.

🔹 Common Variants:
   - Finding MST using Kruskal’s Algorithm (more suitable if edges are given directly instead of adjacency).
   - Sometimes you are asked to **rebuild or update MST** after adding/removing an edge — Prim’s algorithm can be slightly modified for that.

🔹 Time Complexity:
   - O(E log V) using a priority queue (E = number of edges, V = number of vertices)
   - Very efficient for dense graphs.

🔹 Space Complexity:
   - O(V + E) for adjacency list and helper structures.

🔹 Important Tips:
   - Always initialize key[] with INT_MAX.
   - Use a **min-heap** instead of a simple array for optimal performance.
   - If graph nodes are not connected, the algorithm will only cover one connected component.

🔹 When NOT to use:
   - If the graph is **sparse and given as a list of edges**, Kruskal’s is simpler.
   - If edges are dynamically changing (insert/delete), use more advanced MST structures (like dynamic MST algorithms).
*/
