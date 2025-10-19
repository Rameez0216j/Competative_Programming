#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
vector<int> eulerCircuit;

// Recursive function to find Eulerian circuit
void findEulerCircuit(int u) {
    while (!graph[u].empty()) {
        int v = graph[u].back();
        graph[u].pop_back(); // remove edge u->v
        // remove edge v->u as undirected
        graph[v].erase(find(graph[v].begin(), graph[v].end(), u));
        findEulerCircuit(v);
    }
    eulerCircuit.push_back(u);
}

int main() {
    int n, m;
    cin >> n >> m; // n = vertices, m = edges

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected
    }

    // Optional: check all degrees are even
    bool allEven = true;
    for (int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 != 0) allEven = false;
    }

    if (!allEven) {
        cout << "Eulerian circuit does not exist\n";
        return 0;
    }

    findEulerCircuit(1); // start from any vertex
    reverse(eulerCircuit.begin(), eulerCircuit.end());

    cout << "Eulerian Circuit: ";
    for (int u : eulerCircuit) cout << u << " ";
    cout << "\n";
}





/*
🔹 Complexity:

Time: O(E)  -> each edge is visited exactly once
Space: O(E + V)  -> for storing the graph and the Eulerian circuit

🔹 Tips & Tricks:

1. For directed graphs:
   - Ensure in-degree = out-degree for all vertices
   - Remove edges only from the current node's adjacency list

2. For finding Eulerian Path (not circuit):
   - Allow exactly 2 vertices to have odd degree
   - These are the start and end nodes of the path

3. Useful Applications:
   - DNA sequencing problems (Eulerian Path)
   - Route optimization
   - Graph puzzles
*/
