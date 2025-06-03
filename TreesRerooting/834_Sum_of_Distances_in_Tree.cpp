// **************************************** Generalized Rerooting Logic ****************************************
/*
class Solution {
    public:
    // First DFS (post-order): Gathers information from children up to the parent
    void postOrder(int node, int parent,
                   vector<int>& subtreeData, vector<int>& answer,
                   unordered_map<int, vector<int>>& tree) {
        for (int child : tree[node]) {
            if (child == parent) continue;

            postOrder(child, node, subtreeData, answer, tree);

            // Your logic: Update subtreeData[node] and answer[node] using child’s data
            // Example:
            // subtreeData[node] += subtreeData[child];
            // answer[node] += answer[child] + subtreeData[child];
        }
    }

    // Second DFS (pre-order): Propagates the answer from parent to child (rerooting logic)
    void preOrder(int node, int parent,
                  int totalNodes,
                  vector<int>& subtreeData, vector<int>& answer,
                  unordered_map<int, vector<int>>& tree) {
        for (int child : tree[node]) {
            if (child == parent) continue;

            // Your logic: Reroot from node to child by updating answer[child] using answer[node] and subtreeData[child]
            // Example:
            // answer[child] = answer[node] - subtreeData[child] + (totalNodes - subtreeData[child]);

            preOrder(child, node, totalNodes, subtreeData, answer, tree);
        }
    }

    // Driver function
    vector<int> solve(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> tree;
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        vector<int> subtreeData(n, 1); // or initialize based on your problem
        vector<int> answer(n, 0);      // or initialize based on your problem

        postOrder(0, -1, subtreeData, answer, tree);  // Step 1: Gather info bottom-up
        preOrder(0, -1, n, subtreeData, answer, tree); // Step 2: Distribute info top-down (rerooting)

        return answer; // Return the final results
    }
};
*/
// **************************************** Generalized Rerooting Logic ****************************************










// ************************************************ My Solution ************************************************
class Solution {
    public:

    // ------------------------------------------------------------
    // Preprocessing DFS (Post-order traversal)
    // Goal: Compute subtree sizes and distance sums from root (node 0)
    // ------------------------------------------------------------
    void preOrder(int node, int parent, int &n,
                  vector<int> &childCount, vector<int> &nodeCost,
                  unordered_map<int, vector<int>> &adjL) {
        
        for (int child : adjL[node]) {
            if (child == parent) continue; // Avoid traversing back to the parent

            preOrder(child, node, n, childCount, nodeCost, adjL);

            // Accumulate childCount and nodeCost for current node
            // childCount[child] → number of nodes in child's subtree
            // nodeCost[child] → sum of distances from child to all its descendants
            childCount[node] += (1 + childCount[child]);

            // nodeCost[node] = total cost to reach all children and their subtrees
            nodeCost[node] += (1 + childCount[child] + nodeCost[child]);
        }
    }

    // ------------------------------------------------------------
    // Tree Rerooting (Pre-order traversal)
    // Goal: Compute final answer for all nodes using parent’s result
    // ------------------------------------------------------------
    void postOrder(int node, int parent, int &n,
                   vector<int> &childCount, vector<int> &nodeCost,
                   unordered_map<int, vector<int>> &adjL) {
        
        for (int child : adjL[node]) {
            if (child == parent) continue; // Avoid looping back

            // Reroot the tree: calculate cost for child based on parent's cost
            // nodeCost[node] - (childCount[child] + 1): remove child's subtree cost
            // (n - (childCount[child] + 1)): add cost to reach remaining nodes
            nodeCost[child] = nodeCost[node]
                            - (childCount[child] + 1)
                            + (n - (childCount[child] + 1));

            postOrder(child, node, n, childCount, nodeCost, adjL);
        }
    }

    // ------------------------------------------------------------
    // Build the tree and initiates two DFS passes
    // ------------------------------------------------------------
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<int> childCount(n, 0); // Stores subtree size for each node
        vector<int> nodeCost(n, 0);   // Stores sum of distances from each node to all others

        unordered_map<int, vector<int>> adjL; // Adjacency list representation of the tree

        // Build the tree from edge list
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }

        // Step 1: Compute childCount and initial nodeCost from root (node 0)
        preOrder(0, -1, n, childCount, nodeCost, adjL);

        // Step 2: Propagate distances using rerooting technique
        postOrder(0, -1, n, childCount, nodeCost, adjL);

        return nodeCost; // Final distance sums for all nodes
    }
};
// ************************************************ My Solution ************************************************