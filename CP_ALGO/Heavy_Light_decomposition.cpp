/*
Heavy-Light Decomposition (HLD) for LCA Queries

Key Concepts:
1. Tree decomposition into heavy and light edges:
   - Heavy edge: edge to child with largest subtree
   - Light edge: all other edges
2. Each path from root to a node crosses at most O(log n) light edges
3. Allows queries (like sum, max, or LCA) to be reduced to O(log n) segments
4. LCA queries: climb through light edges until common chain

Variables:
adj[node]       --> adjacency list of the tree
parent[node]    --> parent of node in the tree
subtreeSize[node] --> size of subtree rooted at node
depth[node]     --> depth of node from root
heavy[node]     --> child with largest subtree (heavy child) [unbreakable edge]
head[node]      --> head of the heavy path for node
pos[node]       --> position in segment tree or DFS order
currentPos      --> current index while assigning positions
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], subtreeSize[MAXN];
int heavy[MAXN], head[MAXN], pos[MAXN];
int currentPos = 0;

// DFS to compute subtree sizes and heavy child
int dfs(int node, int par) {
    parent[node] = par;
    depth[node] = (par == -1 ? 0 : depth[par] + 1);
    subtreeSize[node] = 1;
    int maxSubtree = 0;
    heavy[node] = -1;

    for (int child : adj[node]) {
        if (child == par) continue;
        int childSize = dfs(child, node);
        subtreeSize[node] += childSize;
        if (childSize > maxSubtree) {
            maxSubtree = childSize;
            heavy[node] = child;
        }
    }
    return subtreeSize[node];
}

// Decompose tree into heavy paths
void decompose(int node, int h) {
    head[node] = h;
    pos[node] = currentPos++;
    if (heavy[node] != -1) {
        // Continue heavy path
        decompose(heavy[node], h); // heavy[node] ==> child with max size and is the unbreakable edge
    }
    
    for (int child : adj[node]) {
        if (child != parent[node] && child != heavy[node]) {
            // New light path starts
            decompose(child, child);
        }
    }
}

// Query LCA using HLD
int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);
        u = parent[head[u]]; // move u up to parent of head
    }
    return (depth[u] < depth[v] ? u : v);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ypu can do this from any node assuming it as root
    dfs(1, -1);       // compute subtree sizes, heavy child
    decompose(1, 1);  // decompose tree

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}

/*
Tips and Tricks:

1. Pattern Recognition:
   - Use HLD when you have a **tree and need path queries** (sum, max, min, gcd) or LCA queries.
   - HLD reduces tree queries into O(log n) segments.

2. Optimization Tips:
   - Heavy paths ensure a node crosses O(log n) light edges on root-to-node path.
   - Combine HLD with **Segment Trees** or **Fenwick Trees** for path queries efficiently.
   - For static LCA queries, simple binary lifting is faster, but HLD is better if you also want **path updates or queries**.

3. Common Problems:
   - Codeforces: "Tree Queries" series, "Heavy Light Decomposition" problems
   - CSES Problem Set: "Path Queries", "Tree Queries"
   - LeetCode: 1249. Minimum Remove to Make Valid Parentheses (as tree-like reasoning), or problems requiring **dynamic path queries**
*/
