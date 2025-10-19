/*
Tree Rerooting Algorithm (Clean and Intuitive Version)
-------------------------------------------------------
Goal: Compute the sum of distances from every node to all others.

Idea:
1️⃣ First DFS computes:
    - subtreeSize[node]: number of nodes in its subtree
    - subtreeDistance[node]: sum of distances from node to all nodes in its subtree

2️⃣ Second DFS (reroot):
    - When root shifts from parent → child:
        • Nodes in child’s subtree become 1 step closer  (-subtreeSize[child])
        • Other nodes become 1 step farther              (+n - subtreeSize[child])

Result:
ans[node] = total sum of distances from node to every other node.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 200005;

vector<int> tree[MAX_NODES];
int subtreeSize[MAX_NODES];
long long subtreeDistance[MAX_NODES];  // Sum of distances from node to all nodes in its subtree
long long totalDistance[MAX_NODES];    // Final result: total distance from node to all other nodes
int totalNodes;

// -------------------- FIRST DFS --------------------
// Computes subtree size and subtree distance for each node
void computeSubtreeInfo(int currentNode, int parentNode) {
    subtreeSize[currentNode] = 1; // Count itself
    subtreeDistance[currentNode] = 0;

    for (int neighbor : tree[currentNode]) {
        if (neighbor == parentNode) continue;

        computeSubtreeInfo(neighbor, currentNode);

        // subtreeDistance[neighbor] → total distance from 'neighbor' to all nodes in its subtree (includes contributions from the entire subtree rooted at 'neighbor').
        // subtreeSize[neighbor] → number of nodes in 'neighbor's subtree, meaning when moving from currentNode → neighbor, each of these nodes adds +1 distance (the edge between currentNode and neighbor) to the total.

        // Add distances of child subtree + one edge per node in child’s subtree
        subtreeDistance[currentNode] += subtreeDistance[neighbor] + subtreeSize[neighbor]; 
        subtreeSize[currentNode] += subtreeSize[neighbor];
    }
}

// -------------------- SECOND DFS (REROOTING) --------------------
// Adjusts subtree info to compute distances for all possible roots
void rerootTree(int currentNode, int parentNode) {
    totalDistance[currentNode] = subtreeDistance[currentNode];

    for (int neighbor : tree[currentNode]) {
        if (neighbor == parentNode) continue;

        // Backup current state
        long long originalCurrentDist = subtreeDistance[currentNode];
        long long originalNeighborDist = subtreeDistance[neighbor];
        int originalCurrentSize = subtreeSize[currentNode];
        int originalNeighborSize = subtreeSize[neighbor];

        // Move root from currentNode → neighbor
        subtreeDistance[currentNode] -= (subtreeDistance[neighbor] + subtreeSize[neighbor]);
        subtreeSize[currentNode] -= subtreeSize[neighbor];
        subtreeDistance[neighbor] += (subtreeDistance[currentNode] + subtreeSize[currentNode]);
        subtreeSize[neighbor] += subtreeSize[currentNode];

        // Continue rerooting
        rerootTree(neighbor, currentNode);

        // Restore original state after returning from recursion
        subtreeDistance[currentNode] = originalCurrentDist;
        subtreeDistance[neighbor] = originalNeighborDist;
        subtreeSize[currentNode] = originalCurrentSize;
        subtreeSize[neighbor] = originalNeighborSize;
    }
}

// -------------------- MAIN FUNCTION --------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> totalNodes;
    for (int i = 0; i < totalNodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    computeSubtreeInfo(1, -1); // Step 1: process info with 1 as root
    rerootTree(1, -1);         // Step 2: reroot to compute for all nodes

    cout << "Sum of distances from each node:\n";
    for (int node = 1; node <= totalNodes; node++) {
        cout << "Node " << node << " → " << totalDistance[node] << "\n";
    }
    return 0;
}
