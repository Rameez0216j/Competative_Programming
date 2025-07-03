/*
=================== de Bruijn Graph Explanation and ASCII Diagram (n = 2, k = 2) ===================
Why Start with "000...0" (n-1) zeros? 
---------------------------
- This is the lexicographically smallest (and simplest) node.
- It always exists in the graph.
- It helps in generating the first `n`-digit code, e.g., for n=3, "000".
- It ensures deterministic and consistent results.
- It’s a natural place to start an Eulerian path that covers all combinations.

Conclusion:
-----------
Using "000...0" (of length n-1) as the starting node in the DFS ensures:
    - All combinations are covered
    - The sequence starts with the most basic pattern
    - Eulerian traversal is clean and efficient


Goal: Generate all possible 2-digit combinations (n = 2) using digits 0 to 1 (k = 2)
      → Combinations: 00, 01, 10, 11

To do this efficiently, we use a de Bruijn graph:
    - Nodes: strings of length (n - 1) = 1 → "0", "1"
    - Edges: add digits (0 or 1) to node → gives a full 2-digit code


Graph Structure (ASCII Diagram):
---------------------------------
           [ "0" ]
           /     \
     0    /       \ 1
         /         \
   [ "0" ]          [ "1" ]
      /  \             / \   
  0  /    \ 1       1 /   \ 0
    /      \         /     \
 ["0"]    [ "1" ]   ["1"]   ["0"]



We make nodes of length (n - 1) because:
- Each node represents the current prefix of length (n - 1).
- From each node, we explore all possible edges by appending digits from 0 to k - 1.
- This way, each edge forms a unique n-digit combination: node + digit.
- If we used full n-digit nodes, we'd revisit the same combinations multiple times,
  leading to redundant nodes and repeated work.

By using (n - 1)-digit nodes, we ensure:
- Every edge contributes exactly one unique n-digit password.
- Duplicate nodes are avoided.
- The graph remains minimal and efficient for Eulerian traversal.

so actual graph will be as below

           [ "0" ]
           /     \
        0 /       \ 1
         /         \
                [ "1" ]
                   / \   
                1 /   \ 0
                 /     \
  
The above edges are not dangling they are actually loops 

we are making nodes as n-1 digits as we are keeping the edges as 0 till k-1 for every node and we check if we are having the n-1 length nodes as only one as again appearing nodes will create redundant nodes



Edge Transitions:
------------------
- "0" + '0' → "00" → next node: "0"
- "0" + '1' → "01" → next node: "1"
- "1" + '0' → "10" → next node: "0"
- "1" + '1' → "11" → next node: "1"

So each edge = 1 full 2-digit password.

Eulerian Path:
---------------
Traverse each edge once → collect digits along the way.

Start at node: "0"

Path example:
"0" → "0" → "1" → "1" → "0"

At each step, record the digit you added:
Collected digits: 00110

Sliding window of size 2 over "00110" gives:
"00", "01", "11", "10" → ✅ all 2-digit codes are present!

Conclusion:
------------
- Nodes are of size (n - 1) so that adding 1 digit gives a full n-digit combination.
- This allows the de Bruijn graph to generate all combinations exactly once.
- We perform Eulerian path traversal to cover all edges and build the shortest string.

======================================================================================
*/




// *************************************** My Solution [Eularian Circuit - BFS] ***************************************
/*
class Solution {
    public:

    void buildEdges(string &node,int k,unordered_map<string,vector<char>> &adjL){
        for(int i=0;i<k;i++){
            adjL[node].push_back('0'+i);
        }
    } 

    string crackSafe(int n, int k) {
        if (n == 1) {
            string res = "";
            for (int i = 0; i < k; ++i)
                res += ('0' + i);
            return res;
        }

        // Below code do not work for n=1 as start="" in that case;

        unordered_map<string,vector<char>> adjL;
        string start(n-1,'0');
        

        // This will also work (lambda function)
        // function<void(string)> buildGraph = [&](string node) {
        //     for (int i = 0; i < k; i++) {
        //         adj[node].push_back('0' + i);
        //     }
        // };


        // Step 1: Building the graph
        unordered_set<string> seen;
        seen.insert(start);
        queue<string> q;
        q.push(start);
        while(!q.empty()){
            string curr_node=q.front();
            q.pop();

            buildEdges(curr_node,k,adjL);
            for(char edgeVal : adjL[curr_node]){
                string next_node=curr_node.substr(1)+edgeVal;
                if(seen.find(next_node)==seen.end()){
                    seen.insert(next_node);
                    q.push(next_node);
                }
            }
        }

        // Step 2: Iterative DFS (Hierholzer's algorithm)
        // Since all the nodes are in loop as we can start from any node (ex: starting from start)
        stack<string> st;
        string result="";
        st.push(start);
        while(!st.empty()){
            string curr=st.top();
            if(!adjL[curr].empty()){
                string next=curr.substr(1)+adjL[curr].back();
                adjL[curr].pop_back(); // explored the edge so delete it
                st.push(next);
            }else{
                st.pop();
                result+=curr.back();
            }
        }

        // start.substr(0,start.size()-1) ==> as the last character is already added to result
        // below code will also work as we are processing the result backways
        reverse(result.begin(),result.end()); 
        return start.substr(0,start.size()-1)+result;

        // This will also work
        // return result+start.substr(0,start.size()-1); 
    }
};
*/
// *************************************** My Solution [Eularian Circuit - BFS] ***************************************








// *************************************** My Solution [Eularian Circuit - DFS] ***************************************
class Solution {
public:
    string result;

    void dfs(string node, int k, unordered_map<string, vector<char>>& adjL) {
        // Lazily build outgoing edges for this node
        if (!adjL.count(node)) {
            for (int i = k - 1; i >= 0; --i) {
                adjL[node].push_back('0' + i);
            }
        }

        // Explore all edges
        while (!adjL[node].empty()) {
            char digit = adjL[node].back();
            adjL[node].pop_back();
            string next_node = node.substr(1) + digit;
            dfs(next_node, k, adjL);
        }

        result += node.back();  // Add the last digit after visiting all edges (post-order)
    }

    string crackSafe(int n, int k) {
        if (n == 1) {
            string res = "";
            for (int i = 0; i < k; ++i)
                res += ('0' + i);
            return res;
        }

        unordered_map<string, vector<char>> adjL;
        string start(n - 1, '0');

        dfs(start, k, adjL);

        reverse(result.begin(), result.end());

        // To complete the cycle, add the first (n-1) prefix at the end
        return start.substr(0,start.size()-1)+result;
    }
};
// *************************************** My Solution [Eularian Circuit - DFS] ***************************************