#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int entryTime[MAXN], exitTime[MAXN];
int timer = 0;

void dfs(int node, int parent) {
    entryTime[node] = timer++;
    for (int child : adj[node]) {
        if (child == parent) continue;
        dfs(child, node);
    }
    exitTime[node] = timer++;
}

// Check if u is ancestor of v
bool isAncestor(int u, int v) {
    return entryTime[u] <= entryTime[v] && exitTime[v] <= exitTime[u];
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1); // root the tree at node 1

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (isAncestor(u, v)) cout << u << " is ancestor of " << v << "\n";
        else cout << u << " is NOT ancestor of " << v << "\n";
    }
}
