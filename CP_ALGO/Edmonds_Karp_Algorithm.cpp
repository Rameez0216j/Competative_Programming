// Edmond karp Algorithm (BFS-based Max Flow)
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Representing "infinite" capacity

int n;                        // Number of nodes in the graph
vector<vector<int>> capacity; // capacity[u][v] = current available capacity from u to v
vector<vector<int>> adj;      // adjacency list of graph

// BFS to find an augmenting path from s to t
int bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; // Mark source as visited with special value
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next] > 0)
            {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

// Main function to compute maximum flow
int maxflow(int s, int t)
{
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = bfs(s, t, parent)))
    {
        flow += new_flow;
        int cur = t;

        // Going from sink to source backward and reducing capacity by newflow foreards and newFlow capacity increased backward
        while (cur != s)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main()
{
    // Example: reading a graph
    int m;         // Number of edges
    cin >> n >> m; // Number of nodes and edges

    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
        capacity[u][v] = cap;
    }

    int source = 0, sink = n - 1; // Example: source = 0, sink = last node
    cout << "Maximum Flow: " << maxflow(source, sink) << endl;

    return 0;
}

// NOTES [Use pen and paper for better understanding via below examle]
/*
Graph Representation (Original Capacities):
Edges with capacities:
1 -> 2 (5), 3 (5), 4 (5)
2 -> 3 (5)
4 -> 3 (5), 5 (10)
3 -> 6 (10)
6 -> 5 (10)

Source = 1, Sink = 5

-----------------------------------
Step 1: First BFS Augmenting Path

Path 1: 1 -> 3 -> 6 -> 5
Bottleneck = min(5,10,10) = 5

Update capacities:
Forward edges: 1->3 = 0, 3->6 = 5, 6->5 = 5
Reverse edges: 3->1 = 5, 6->3 = 5, 5->6 = 5

Flow so far = 5

-----------------------------------
Step 2: Second BFS Augmenting Path

Path 2: 1 -> 4 -> 3 -> 6 -> 5
Check residual capacities:
1->4 = 5
4->3 = 5
3->6 = 5 (after Path1)
6->5 = 5 (after Path1)
Bottleneck = 5

Update capacities:
Forward edges: 1->4 = 0, 4->3 = 0, 3->6 = 0, 6->5 = 0
Reverse edges: 4->1 = 5, 3->4 = 5, 6->3 = 10, 5->6 = 10

Flow so far = 10

-----------------------------------
Step 3: Third BFS Augmenting Path

Path 3: 1 -> 2 -> 3 -> 4 -> 5
Check residual capacities:
1->2 = 5
2->3 = 5
3->4 = 5 (from reverse edge after Path2)
4->5 = 10
Bottleneck = 5

Update capacities:
Forward edges: 1->2 = 0, 2->3 = 0, 3->4 = 0, 4->5 = 5
Reverse edges: 2->1 = 5, 3->2 = 5, 4->3 = 5, 5->4 = 5

Flow so far = 15

-----------------------------------
How Residual Edges Help:

- In Path3, 3->4 uses **residual edge** created after Path2:
    - Path2 sent flow 1->4->3->6->5, creating 3->4 reverse edge with capacity = 5
    - Path3 can now “borrow” that flow to push additional flow through 4->5
- Without residual edges, Path3 wouldn’t be able to use 3->4 because original 4->3 capacity is exhausted
- Residual edges effectively allow BFS/DFS to **reroute previous flows**, ensuring leftover capacities are utilized
- Flow always increases by bottleneck of each augmenting path

-----------------------------------
Summary:

- Forward edges: remaining capacity along edge
- Reverse edges: “give back” previously sent flow for rerouting
- BFS explores both to find new augmenting paths
- Maximum flow = sum of bottlenecks along all augmenting paths
- Residual edges are key to **using leftover capacity efficiently**
*/

/*
Time Complexity of Edmonds-Karp Algorithm (Max Flow):

Key Points:

1. Edmonds-Karp uses BFS to find the shortest augmenting path in terms of
   number of edges from source to sink.

2. Let:
    V = number of vertices (nodes)
    E = number of edges

3. Each BFS has a complexity of O(E):
    - BFS explores all edges in the residual graph
    - Each edge is checked at most once per BFS

4. How many augmenting paths can there be at most?
    - Each time we send flow along a shortest path, at least one edge
      becomes saturated (capacity becomes 0)
    - In Edmonds-Karp, each edge can become saturated **at most O(V/2) times**
      (because the shortest path length increases by at least 1 after edge saturation)
    - Maximum number of augmenting paths = O(V * E)

5. Therefore, total time complexity:
    - O(number of augmenting paths * time per BFS)
    - O(V * E * E) = O(V * E^2)

-----------------------------------------
Summary:

- BFS: O(E)
- Number of augmenting paths: O(V * E)
- Total complexity: O(V * E^2)

-----------------------------------------
Important Notes / Optimization Tips:

- For small graphs (V ~ 1000, E ~ 10000), Edmonds-Karp is fine.
- For large networks, consider Dinic’s Algorithm (O(E * V^2)) or
  Push-Relabel methods for better efficiency.
- Time complexity is independent of actual capacities, only edges & nodes matter.
- The algorithm guarantees termination because capacities are integers and
  flow always increases by at least 1 unit per augmenting path.
*/
