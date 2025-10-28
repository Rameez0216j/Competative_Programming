/*
   Kuhn's Algorithm → Maximum Bipartite Matching using DFS (augmenting paths)

   🧩 Key Terms:
   -------------------------------------------------
   n  → number of vertices in the left partition (L)
   k  → number of vertices in the right partition (R)
   g  → adjacency list from L to R
   mt[i] → matched vertex in L for vertex i in R (matching table)
   used[v] → visited marker for DFS to avoid revisiting during one attempt

   Goal:
   - Pair as many vertices from Left set (L) with Right set (R)
   - Such that no two edges share an endpoint (i.e., no overlap)
*/

#include <bits/stdc++.h>
using namespace std;

// DFS function to find an augmenting path
bool tryKuhn(int leftNode, vector<vector<int>> &graph, vector<int> &matchRight, vector<bool> &used) {
    if (used[leftNode])
        return false; // already visited in current DFS
    used[leftNode] = true;

    // Explore all neighbors in the Right set
    for (int rightNode : graph[leftNode]) {
        /*
           Case 1: rightNode is not matched yet → we can match directly
           Case 2: rightNode is already matched → try to find an alternate path
                   for its current match (recursively tryKuhn)
        */
        if (matchRight[rightNode] == -1 || tryKuhn(matchRight[rightNode], graph, matchRight, used)) {
            matchRight[rightNode] = leftNode; // assign leftNode to this rightNode
            return true; // augmenting path found
        }
    }

    return false; // no augmenting path found
}

int main() {
    int n, k, edges;
    cin >> n >> k >> edges;

    vector<vector<int>> graph(n); // adjacency list from Left → Right
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        // assuming 0-based indexing
        graph[u].push_back(v);
    }

    vector<int> matchRight(k, -1); // matchRight[j] = i means j in Right matched with i in Left

    // Try to find a match for every vertex in Left set
    for (int leftNode = 0; leftNode < n; ++leftNode) {
        vector<bool> used(n, false);
        tryKuhn(leftNode, graph, matchRight, used);
    }

    cout << "\nMaximum Matching Pairs:\n";
    for (int j = 0; j < k; ++j) {
        if (matchRight[j] != -1)
            cout << "Left " << matchRight[j] + 1 << "  <-->  Right " << j + 1 << "\n";
    }

    return 0;
}

/*
🧩 Explanation:
---------------
1️⃣ We iterate through each vertex in Left set.
2️⃣ For each vertex, we try to find a free Right vertex.
3️⃣ If not free, we recursively “reroute” the match of that Right vertex.
4️⃣ Each successful rerouting increases total matching by 1.

This DFS-based approach finds *augmenting paths* → paths that can increase the size of the matching.
*/














/*
====================================================================
📘 Example: Maximum Bipartite Matching (Kuhn’s Algorithm)
====================================================================

Left Set (L):   L1, L2, L3
Right Set (R):  R1, R2

Edges (connections):
---------------------
L1 → R1
L2 → R1
L2 → R2
L3 → R2

🧩 Step-by-step reasoning:
--------------------------

Each Left node can be connected to some Right nodes.
We need to form pairs (L → R) such that:
 - No Left node is used more than once.
 - No Right node is used more than once.

Lets explore possible valid matchings:

✅ Matching 1:
   L1 → R1
   L2 → R2
   Size = 2

✅ Matching 2:
   L2 → R1
   L3 → R2
   Size = 2

❌ Invalid Example:
   L1 → R1
   L2 → R1  (❌ Both share R1)

Hence, the **maximum number of pairs (maximum matching)** = 2

There can be multiple valid maximum matchings having the same size.
Kuhn’s Algorithm will find **one of them**, not necessarily all.

--------------------------------------------------------------
🎯 Intuitive Analogy:
--------------------------------------------------------------
Think of Left nodes as “people” and Right nodes as “jobs.”
Each person can do some jobs (edges define eligibility).
You want to assign as many people as possible unique jobs.
That’s what Kuhn’s Algorithm achieves — the **maximum possible pairing**.

--------------------------------------------------------------
🧠 Dry Run Idea:
--------------------------------------------------------------
DFS starts from each Left node trying to find a free Right node:
 - L1 matched to R1
 - L2 tries R1 → already taken by L1 → looks for alternate → finds R2 → matched
 - L3 tries R2 → already taken by L2 → no alternate → fails

Result: {L1→R1, L2→R2} → Maximum size = 2
====================================================================
*/
