// Exactly same to findBridge algo


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
int discoveryTime[MAXN], low[MAXN];
bool visited[MAXN], isArticulationPoint[MAXN];
int timer = 0;

void findArticulationPoints(int node, int parent) {
    visited[node] = true;
    discoveryTime[node] = low[node] = timer++;
    int children = 0; // count of children in DFS tree

    for (int neighbor : graph[node]) {
        if (neighbor == parent) continue;

        if (visited[neighbor]) {
            // back edge
            low[node] = min(low[node], discoveryTime[neighbor]);
        } else {
            // tree edge
            children++;
            findArticulationPoints(neighbor, node);
            low[node] = min(low[node], low[neighbor]);

            // Articulation point check (not root)
            if (parent != -1 && low[neighbor] >= discoveryTime[node])
                isArticulationPoint[node] = true; // always parent becomes articualtion points as child can be a leaf [compared to findBridge algo]
        }
    }

    // Root special case
    if (parent == -1 && children > 1)
        isArticulationPoint[node] = true;
}

int main() {
    int n, m;
    cin >> n >> m; // n = vertices, m = edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected graph
    }

    // Run DFS from all unvisited nodes (handle disconnected graph)
    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            findArticulationPoints(i, -1);
    }

    cout << "Articulation Points:\n";
    for (int i = 1; i <= n; i++) {
        if (isArticulationPoint[i])
            cout << i << " ";
    }
    cout << "\n";
}

/*
🔹 Complexity:

Time: O(V + E)  -> DFS visits every node and edge once
Space: O(V + E)  -> adjacency list + arrays

🔹 Tips & Tricks:

1. Root node with >1 child in DFS tree is always an articulation point.
2. Non-root node u is articulation point if there exists a child v with low[v] >= discoveryTime[u].
3. Useful in network analysis, critical points in communication networks, and connectivity problems.
*/
