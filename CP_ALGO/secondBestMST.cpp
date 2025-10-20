/*
----------------------------------------------------------
     Second Best Minimum Spanning Tree - Data Structures
----------------------------------------------------------

1️⃣ Edge Structure: `struct Edge`
   - Stores information about an edge in the graph:
       • fromNode   → starting vertex of the edge
       • toNode     → ending vertex of the edge
       • weight     → weight of the edge
       • edgeId     → unique identifier of the edge (used to mark if it is in MST)
   - Purpose: Used to sort edges for Kruskal’s algorithm and reference edges later.

2️⃣ Graph Representation: `vector<vector<pair<int,int>>> adjacencyList`
   - adjacencyList[node] = list of {neighbor, edgeWeight} pairs
   - Stores the **edges of the MST** (not the original graph)
   - Purpose: Used for DFS and LCA preprocessing to quickly traverse the tree.

3️⃣ Disjoint Set Union (DSU):
   - `dsuParent[node]` → parent of node in DSU
   - `dsuSize[node]`   → size of the set (used for union by size optimization)
   - Purpose: Kruskal’s algorithm uses DSU to efficiently check if adding an edge forms a cycle.
   - findSet(node) → finds root of node
   - unionSets(a, b) → merges sets containing a and b

4️⃣ MST Helpers:
   - `nodeDepth[node]` → depth of node in the MST (root = 0 or 1)
   - `isEdgeInMST[edgeId]` → marks whether a particular edge is included in MST

5️⃣ Binary Lifting (LCA) Tables:
   - `binaryParent[node][j]` → 2^j-th ancestor of node in the MST
       • Example: binaryParent[node][0] = immediate parent
       • binaryParent[node][1] = parent of parent
       • binaryParent[node][j] = parent of binaryParent[node][j-1]
   - Purpose: Precompute ancestors for fast LCA queries (O(log N))

6️⃣ Max Edge Tables (Binary Lifting):
   - `maxEdgeUp[node][j]` = pair<int,int> storing **top 2 heaviest edges**
     from node up to its 2^j-th ancestor
       • first → heaviest edge weight
       • second → second heaviest edge weight (or -1 if not present)
   - Purpose: When adding a non-MST edge, we need to find the **heaviest edge on the path** in MST to check if replacing it gives a smaller total weight.
   - combineEdges(a, b) → merges two pairs to maintain top 2 distinct heaviest edges (max 2 edges)

7️⃣ Utility Functions:
   - `preprocessDFS(node, parent, edgeWeight)` → DFS to initialize:
       • depth[node], binaryParent[node][0], maxEdgeUp[node][0]
   - `getMaxEdgesOnPath(nodeA, nodeB)` → queries top 2 heaviest edges along path between two nodes using binary lifting

----------------------------------------------------------
🧠 Summary:
- DSU + Kruskal → build MST
- adjacencyList → stores MST edges
- nodeDepth, binaryParent → support LCA queries
- maxEdgeUp → support fast retrieval of heaviest edges on any path in MST
- Top 2 edges are stored to handle the edge case when non-MST edge has same weight as heaviest edge in cycle
----------------------------------------------------------
*/




/*
------------------------------------------
     Second Best Minimum Spanning Tree
------------------------------------------

Step 1️⃣ : Build MST using Kruskal’s algorithm.
Step 2️⃣ : For every non-MST edge, try replacing 
           the heaviest edge in the cycle it forms 
           to see if we can get a smaller total cost.

We use Binary Lifting (LCA) to quickly find 
the heaviest edge on a path between two nodes.
------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/* ---------- Edge Structure ---------- */
struct Edge {
    int fromNode, toNode, weight, edgeId;
    bool operator<(const Edge &other) const { 
        return weight < other.weight; 
    }
};

/* ---------- Constants ---------- */
const int MAX_NODES = 200005;
const int LOG_LIMIT = 21;

/* ---------- Graph and DSU Data ---------- */
int totalNodes, totalEdges;
vector<Edge> edgeList;
vector<vector<pair<int, int>>> adjacencyList(MAX_NODES); // adjacencyList[node] = {neighbor, edgeWeight}

/* ---------- DSU Helpers ---------- */
vector<int> dsuParent(MAX_NODES), dsuSize(MAX_NODES);

/* ---------- MST and LCA Helpers ---------- */
vector<int> nodeDepth(MAX_NODES), isEdgeInMST(MAX_NODES);
vector<vector<int>> binaryParent(MAX_NODES, vector<int>(LOG_LIMIT, -1));
vector<vector<pair<int, int>>> maxEdgeUp(MAX_NODES, vector<pair<int, int>>(LOG_LIMIT, {-1, -1}));

/* ---------- DSU Implementation ---------- */
int findSet(int node) {
    return (dsuParent[node] == node) ? node : dsuParent[node] = findSet(dsuParent[node]);
}

bool unionSets(int nodeA, int nodeB) {
    nodeA = findSet(nodeA);
    nodeB = findSet(nodeB);
    if (nodeA == nodeB) return false;

    if (dsuSize[nodeA] < dsuSize[nodeB]) swap(nodeA, nodeB);
    dsuParent[nodeB] = nodeA;
    dsuSize[nodeA] += dsuSize[nodeB];
    return true;
}

/* ---------- Utility Function ---------- */
// Combines two {max1, max2} pairs to get the two largest unique edge weights
pair<int, int> combineEdges(pair<int, int> a, pair<int, int> b) {
    vector<int> values = {a.first, a.second, b.first, b.second};
    sort(values.rbegin(), values.rend());
    values.erase(unique(values.begin(), values.end()), values.end());
    return {values[0], values.size() > 1 ? values[1] : -1};
}

/* ---------- DFS for LCA Preprocessing ---------- */
void preprocessDFS(int currentNode, int parentNode, int edgeWeight) {
    binaryParent[currentNode][0] = parentNode;
    maxEdgeUp[currentNode][0] = {edgeWeight, -1};

    for (auto [neighbor, weight] : adjacencyList[currentNode]) {
        if (neighbor == parentNode) continue;
        nodeDepth[neighbor] = nodeDepth[currentNode] + 1;
        preprocessDFS(neighbor, currentNode, weight);
    }
}

/* ---------- LCA Query: Get Heaviest Edges on Path ---------- */
pair<int, int> getMaxEdgesOnPath(int nodeA, int nodeB) {
    pair<int, int> result = {-1, -1};

    if (nodeDepth[nodeA] < nodeDepth[nodeB]) swap(nodeA, nodeB);

    // Lift nodeA up to match depth of nodeB
    for (int i = LOG_LIMIT - 1; i >= 0; i--) {
        if (nodeDepth[nodeA] - (1 << i) >= nodeDepth[nodeB]) {
            result = combineEdges(result, maxEdgeUp[nodeA][i]);
            nodeA = binaryParent[nodeA][i];
        }
    }

    if (nodeA == nodeB) return result;

    // Lift both nodes simultaneously until they meet
    for (int i = LOG_LIMIT - 1; i >= 0; i--) {
        if (binaryParent[nodeA][i] != -1 && binaryParent[nodeA][i] != binaryParent[nodeB][i]) {
            result = combineEdges(result, combineEdges(maxEdgeUp[nodeA][i], maxEdgeUp[nodeB][i]));
            nodeA = binaryParent[nodeA][i];
            nodeB = binaryParent[nodeB][i];
        }
    }

    // Combine last edges before LCA
    result = combineEdges(result, combineEdges(maxEdgeUp[nodeA][0], maxEdgeUp[nodeB][0]));
    return result;
}

/* ---------- Main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> totalNodes >> totalEdges;

    // Initialize DSU
    for (int i = 1; i <= totalNodes; i++) {
        dsuParent[i] = i;
        dsuSize[i] = 1;
    }

    // Input edges
    for (int i = 0; i < totalEdges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edgeList.push_back({u, v, w, i});
    }

    /* ---------- Step 1️⃣: Build MST (Kruskal) ---------- */
    sort(edgeList.begin(), edgeList.end());
    long long mstWeight = 0;

    for (auto &edge : edgeList) {
        if (unionSets(edge.fromNode, edge.toNode)) {
            mstWeight += edge.weight;
            isEdgeInMST[edge.edgeId] = 1;
            adjacencyList[edge.fromNode].push_back({edge.toNode, edge.weight});
            adjacencyList[edge.toNode].push_back({edge.fromNode, edge.weight});
        }
    }

    /* ---------- Step 2️⃣: Binary Lifting Preprocessing ---------- */
    preprocessDFS(1, -1, -1);

    for (int j = 1; j < LOG_LIMIT; j++) {
        for (int node = 1; node <= totalNodes; node++) {
            if (binaryParent[node][j - 1] != -1) {
                int ancestor = binaryParent[node][j - 1];
                binaryParent[node][j] = binaryParent[ancestor][j - 1];
                maxEdgeUp[node][j] = combineEdges(maxEdgeUp[node][j - 1], maxEdgeUp[ancestor][j - 1]);
            }
        }
    }

    /* ---------- Step 3️⃣: Evaluate Non-MST Edges ---------- */
    long long secondBestMST = LLONG_MAX;

    for (auto &edge : edgeList) {
        if (!isEdgeInMST[edge.edgeId]) {
            auto maxEdges = getMaxEdgesOnPath(edge.fromNode, edge.toNode);

            if (maxEdges.first != -1 && maxEdges.first != edge.weight)
                secondBestMST = min(secondBestMST, mstWeight + edge.weight - maxEdges.first);
            else if (maxEdges.second != -1)
                secondBestMST = min(secondBestMST, mstWeight + edge.weight - maxEdges.second);
        }
    }

    cout << secondBestMST << "\n";
    return 0;
}

/* ------------------------------------------------
   🧠 Tips & Tricks — Problem Recognition
------------------------------------------------
- Use when asked for "Second Best MST".
- Check how adding/removing an edge affects MST.
- Binary Lifting allows O(log N) queries for max edges.

- Time Complexity:
    • Kruskal → O(M log M)
    • LCA Preprocessing → O(N log N)
    • Query per edge → O(M log N)
    ✅ Overall → O((M + N) log N)
------------------------------------------------ */