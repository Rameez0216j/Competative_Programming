/*
    side[i] --> represents which side (color/group) node 'i' belongs to.
                -1 means unvisited
                 0 and 1 represent two different sides (colors)
    adj[v]  --> adjacency list storing all neighbors of vertex 'v'
    isBipartite --> flag to track if the graph remains bipartite
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // number of nodes and edges
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // assuming 0-based indexing
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> side(n, -1); // -1 means unvisited node
    bool isBipartite = true;

    // Process all connected components
    for (int start = 0; start < n; ++start) {
        if (side[start] == -1) { // start BFS only for unvisited component
            queue<int> q;
            q.push(start);
            side[start] = 0; // assign first color (0)

            while (!q.empty()) {
                int currentNode = q.front();
                q.pop();

                for (int neighbor : adj[currentNode]) {
                    if (side[neighbor] == -1) {
                        // Assign opposite color to neighbor using XOR
                        side[neighbor] = side[currentNode] ^ 1;
                        q.push(neighbor);
                    } else if (side[neighbor] == side[currentNode]) {
                        // Adjacent nodes have same color → not bipartite
                        isBipartite = false;
                    }
                }
            }
        }
    }

    cout << (isBipartite ? "YES" : "NO") << endl;
    return 0;
}

/*
  🔍 Explanation:
  ----------------
  - A graph is bipartite if you can divide its vertices into two sets
    such that no edge connects vertices within the same set.
  - In BFS, we "color" each node 0 or 1.
  - Every neighbor gets the opposite color using XOR (^1).
  - If we ever find two connected nodes with the same color → Not bipartite.
*/
