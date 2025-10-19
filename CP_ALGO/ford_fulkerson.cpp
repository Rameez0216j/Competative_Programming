/*
Ford-Fulkerson Algorithm (DFS-based Max Flow):
This algorithm computes the maximum flow from a source `s` to a sink `t`
using depth-first search (DFS) to find augmenting paths in the residual graph.

Key Components:
n                --> number of nodes in the graph
capacity[u][v]   --> remaining capacity of edge u->v
adj[u]           --> adjacency list of node u
visited[u]       --> marks if a node has been visited in current DFS
INF              --> represents "infinite" capacity
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Representing infinite capacity

int n; // number of nodes
vector<vector<int>> capacity; // capacity[u][v] = available capacity
vector<vector<int>> adj;      // adjacency list

// DFS to find an augmenting path from node u to sink t
// Returns the flow along this path
int dfs(int u, int t, int flow, vector<bool>& visited) {
    if (u == t) return flow; // reached sink
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) { // can push flow
            int bottleneck = dfs(v, t, min(flow, capacity[u][v]), visited);
            if (bottleneck > 0) {
                // Update residual capacities
                capacity[u][v] -= bottleneck;
                capacity[v][u] += bottleneck; // create reverse edge
                return bottleneck;
            }
        }
    }

    return 0; // no augmenting path found from u
}

// Main function to compute maximum flow from source s to sink t
int maxflow(int s, int t) {
    int flow = 0;
    while (true) {
        vector<bool> visited(n, false);
        int new_flow = dfs(s, t, INF, visited);
        if (new_flow == 0) break; // no more augmenting paths
        flow += new_flow;
    }
    return flow;
}

/*
Tips and Tricks / Pattern Recognition:

1. Pattern Recognition:
   - Problem mentions "maximum flow", "network capacity", or "bipartite matching".
   - DFS version explores one augmenting path at a time (may not be shortest path).

2. Residual Graph:
   - Forward edges: remaining capacity
   - Reverse edges: previously sent flow that can be undone to form new paths

3. Time Complexity:
   - O(F * E), where F = max flow, E = number of edges
   - Worst-case can be bad if capacities are large integers
   - Not guaranteed to terminate efficiently with fractional capacities
   - Edmonds-Karp improves this using BFS → O(V * E^2)

4. Hard LeetCode Problems (Max Flow / Ford-Fulkerson):
   - 1168. Optimize Water Distribution in a Village
   - 846. Hand of Straights (flow variant)
   - 857. Minimum Cost to Hire K Workers
   - 780. Reaching Points (can be reduced to network flow)
*/
