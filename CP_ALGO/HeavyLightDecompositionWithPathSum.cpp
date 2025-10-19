/*
Heavy-Light Decomposition (HLD) + Segment Tree for Path Sum Queries

Key Concepts:
1. Heavy-Light Decomposition splits the tree into heavy paths.
2. Segment Tree is built on the DFS order of the nodes.
3. To query the sum along path u -> v:
   - Move u and v up along heavy paths until they share the same heavy path (head)
   - Sum the segments along the way

Variables:
adj[node]       --> adjacency list of the tree
parent[node]    --> parent of node
subtreeSize[node] --> size of subtree rooted at node
depth[node]     --> depth of node
heavy[node]     --> child with largest subtree
head[node]      --> head of the heavy path
pos[node]       --> position of node in segment tree
currentPos      --> current index while assigning positions
segTree[]       --> segment tree storing values
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], subtreeSize[MAXN];
int heavy[MAXN], head[MAXN], pos[MAXN];
int currentPos = 0;
long long segTree[4*MAXN], nodeValue[MAXN];

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
    if (heavy[node] != -1)
        decompose(heavy[node], h);
    for (int child : adj[node]) {
        if (child != parent[node] && child != heavy[node])
            decompose(child, child); // start new path
    }
}

// Segment Tree functions
void buildSegmentTree(int node, int start, int end) {
    if (start == end) {
        segTree[node] = nodeValue[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2*node, start, mid);
        buildSegmentTree(2*node+1, mid+1, end);
        segTree[node] = segTree[2*node] + segTree[2*node+1];
    }
}

void updateSegmentTree(int node, int start, int end, int idx, long long value) {
    if (start == end) {
        segTree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) updateSegmentTree(2*node, start, mid, idx, value);
        else updateSegmentTree(2*node+1, mid+1, end, idx, value);
        segTree[node] = segTree[2*node] + segTree[2*node+1];
    }
}

long long querySegmentTree(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0; // completely outside
    if (l <= start && end <= r) return segTree[node]; // completely inside
    int mid = (start + end) / 2;
    return querySegmentTree(2*node, start, mid, l, r) +
           querySegmentTree(2*node+1, mid+1, end, l, r);
}

// Query sum along path u -> v
long long queryPath(int u, int v) {
    long long res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += querySegmentTree(1, 0, currentPos-1, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += querySegmentTree(1, 0, currentPos-1, pos[u], pos[v]);
    return res;
}

// Update value of a node
void updateNode(int u, long long value) {
    updateSegmentTree(1, 0, currentPos-1, pos[u], value);
}

int main() {
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> nodeValue[i-1]; // initial values
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);           // compute subtree sizes and heavy child
    decompose(0, 0);      // decompose tree
    vector<long long> dfsOrder(n);
    for (int i = 0; i < n; ++i) dfsOrder[pos[i]] = nodeValue[i];
    for (int i = 0; i < n; ++i) nodeValue[i] = dfsOrder[i];

    buildSegmentTree(1, 0, n-1);

    cin >> q;
    while (q--) {
        string type; cin >> type;
        if (type == "update") {
            int u; long long val;
            cin >> u >> val;
            updateNode(u, val);
        } else if (type == "query") {
            int u, v;
            cin >> u >> v;
            cout << queryPath(u, v) << "\n";
        }
    }
}

/*
Tips and Tricks:

1. Pattern Recognition:
   - Use HLD + segment tree when you need **path queries or updates** on a tree.
   - Associative operations: sum, max, min, xor, gcd, etc.

2. Optimization Tips:
   - Each path query reduces to O(log n) segments (light edges).
   - For edge queries instead of nodes, store edge value in the child node.

3. Common Problems:
   - CSES Path Queries
   - Codeforces Tree Queries
   - AtCoder Tree + Path queries
*/
