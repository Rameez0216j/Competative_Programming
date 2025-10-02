// Solution : https://www.youtube.com/watch?v=W1xTqEcoSkI
// ***************************************** My Solution *****************************************
class Solution
{
public:
    void markNodes(int mark, int node, int parent, unordered_map<int, vector<int>> &adjL, vector<int> &marking)
    {
        marking[node] = mark;
        for (int nbr : adjL[node])
        {
            if (nbr != parent)
                markNodes(!mark, nbr, node, adjL, marking);
        }
    }

    vector<int> maxTargetNodes(vector<vector<int>> &edges1, vector<vector<int>> &edges2)
    {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        unordered_map<int, vector<int>> adjL1, adjL2;
        for (auto edge : edges1)
        {
            int u = edge[0];
            int v = edge[1];

            adjL1[u].push_back(v);
            adjL1[v].push_back(u);
        }

        for (auto edge : edges2)
        {
            int u = edge[0];
            int v = edge[1];

            adjL2[u].push_back(v);
            adjL2[v].push_back(u);
        }

        vector<int> marking1(n, -1), marking2(m, -1);
        markNodes(0, 0, -1, adjL1, marking1);
        markNodes(0, 0, -1, adjL2, marking2);

        int marked1_0 = 0;
        int marked1_1 = 0;
        for (int val : marking1)
            val == 0 ? marked1_0++ : marked1_1++;

        int marked2_0 = 0;
        int marked2_1 = 0;
        for (int val : marking2)
            val == 0 ? marked2_0++ : marked2_1++;
        int maxMark2 = max(marked2_0, marked2_1);

        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++)
        {
            ans[i] = marking1[i] == 0 ? marked1_0 + maxMark2 : marked1_1 + maxMark2;
        }

        return ans;
    }
};
// ***************************************** My Solution *****************************************

// ******************** My Solution [Cleaned and with better naming convention] ********************
/*
class Solution {
    public:
    // Helper function to mark nodes in alternating fashion (like bipartite coloring)
    // currentColor -> 0 or 1, assigned alternately to nodes
    // currentNode -> node being visited
    // parentNode -> parent of currentNode, to avoid revisiting
    // adjacencyList -> adjacency list of the tree
    // colorAssignment -> stores the color assigned to each node
    void assignColors(int currentColor, int currentNode, int parentNode,
                      unordered_map<int, vector<int>> &adjacencyList,
                      vector<int> &colorAssignment) {
        // Assign current color to this node
        colorAssignment[currentNode] = currentColor;

        // Visit all neighbors and assign opposite color
        for (int neighbor : adjacencyList[currentNode]) {
            if (neighbor != parentNode) {
                assignColors(!currentColor, neighbor, currentNode, adjacencyList, colorAssignment);
            }
        }
    }

    vector<int> maxTargetNodes(vector<vector<int>>& tree1Edges, vector<vector<int>>& tree2Edges) {
        int tree1Nodes = tree1Edges.size() + 1; // number of nodes in tree1
        int tree2Nodes = tree2Edges.size() + 1; // number of nodes in tree2

        // Step 1: Build adjacency lists for both trees
        unordered_map<int, vector<int>> tree1Adjacency, tree2Adjacency;
        for (auto &edge : tree1Edges) {
            int u = edge[0], v = edge[1];
            tree1Adjacency[u].push_back(v);
            tree1Adjacency[v].push_back(u);
        }
        for (auto &edge : tree2Edges) {
            int u = edge[0], v = edge[1];
            tree2Adjacency[u].push_back(v);
            tree2Adjacency[v].push_back(u);
        }

        // Step 2: Perform bipartite-like coloring on both trees
        vector<int> tree1Colors(tree1Nodes, -1), tree2Colors(tree2Nodes, -1);
        assignColors(0, 0, -1, tree1Adjacency, tree1Colors);
        assignColors(0, 0, -1, tree2Adjacency, tree2Colors);

        // Step 3: Count nodes of each color in tree1
        int tree1Color0Count = 0, tree1Color1Count = 0;
        for (int color : tree1Colors) {
            if (color == 0) tree1Color0Count++;
            else tree1Color1Count++;
        }

        // Step 4: Count nodes of each color in tree2
        int tree2Color0Count = 0, tree2Color1Count = 0;
        for (int color : tree2Colors) {
            if (color == 0) tree2Color0Count++;
            else tree2Color1Count++;
        }

        // Step 5: Choose the larger partition from tree2
        int maxTree2Partition = max(tree2Color0Count, tree2Color1Count);

        // Step 6: For each node in tree1, compute max target nodes
        vector<int> result(tree1Nodes, 0);
        for (int node = 0; node < tree1Nodes; node++) {
            if (tree1Colors[node] == 0) {
                result[node] = tree1Color0Count + maxTree2Partition;
            } else {
                result[node] = tree1Color1Count + maxTree2Partition;
            }
        }

        return result;
    }
};
*/
// ******************** My Solution [Cleaned and with better naming convention] ********************
