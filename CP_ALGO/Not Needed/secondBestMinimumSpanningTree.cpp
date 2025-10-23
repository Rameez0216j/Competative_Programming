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
// [This is done on MST] ==> adjacencyList is MST actually
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
    preprocessDFS(1, -1, -1); // parent = -1 and no edge for parent so -1 (dummy value) [filling first row]
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
   🔹 Use this algorithm when:
       - You're asked for the “Second Best” MST.
       - You need to evaluate how adding/removing 
         an edge affects total MST weight.
       - You must find the heaviest edge on a 
         path between two nodes efficiently.

   🔹 Tools used:
       - Kruskal’s Algorithm → Builds MST efficiently using DSU.
       - Binary Lifting (LCA) → Allows fast O(log N) queries for 
         max edge weights on any path.

   🔹 Time Complexity:
       • Kruskal’s → O(M log M)
       • LCA Preprocessing → O(N log N)
       • Queries per edge → O(M log N)
       ✅ Overall → O((M + N) log N)

   🔹 Pattern Recognition:
       Look for phrases like:
         “Second minimum spanning tree”,
         “Alternative connection cost”,
         “Edge replacement impact”,
         “Heaviest edge on path”.

   🔹 Real-world Analogy:
       Imagine building the cheapest network 
       of roads connecting cities (MST). 
       Then, a new contractor proposes a different road —
       this algorithm helps you check if it 
       can create a *slightly cheaper* alternative MST.
------------------------------------------------ */
