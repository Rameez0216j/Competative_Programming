// up[node][i] = 2^i-th ancestor of node
// up[node][i] = up[up[node][i-1]][i-1]





#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 20; // because 2^20 > 10^6
vector<int> tree[MAXN];
int up[MAXN][LOG]; // up[node][i] = 2^i-th ancestor of node
int depth[MAXN];
int n;

// DFS to fill up table and depth
void dfs(int node, int parent) {
    up[node][0] = parent; // immediate parent
    for (int i = 1; i < LOG; i++) {
        if (up[node][i-1] != -1)
            up[node][i] = up[up[node][i-1]][i-1];
        else
            up[node][i] = -1;
    }

    for (int child : tree[node]) {
        if (child == parent) continue;
        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

// Function to get k-th ancestor of node
int getKthAncestor(int node, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) {
            node = up[node][i];
            if (node == -1) return -1; // no such ancestor
        }
    }
    return node;
}

int main() {
    int q;
    cin >> n >> q; // number of nodes and queries
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    memset(up, -1, sizeof(up));
    depth[0] = 0;
    dfs(0, -1); // root at node 0

    while (q--) {
        int node, k;
        cin >> node >> k;
        cout << getKthAncestor(node, k) << "\n";
    }
}
