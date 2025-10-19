#include <bits/stdc++.h>
using namespace std;

class EularianCircuit{
    public:
    // 2097. Valid Arrangement of Pairs
    vector<vector<int>> validArrangement(vector<vector<int>> &pairs){
        // constructing adjacency_matrix,in_degree,out_degree
        unordered_map<int, vector<int>> adjM;
        unordered_map<int, int> in_degree, out_degree;
        for (auto pair : pairs)
        {
            int u = pair[0];
            int v = pair[1];
            adjM[u].push_back(v);

            out_degree[u]++;
            in_degree[v]++;
        }

        // finding start node
        int start = -1;
        for (auto &[node, _] : adjM){
            if (out_degree[node] - in_degree[node] == 1)
                start = node;
        }
        if (start == -1) start = pairs[0][0];

        // Hierholzer's Algorithm to find Eulerian Path
        stack<int> curr_st;
        vector<int> path;
        curr_st.push(start);
        cout << start << " ";

        while (!curr_st.empty())
        {
            int curr = curr_st.top();

            if (adjM[curr].size() > 0)
            {
                int next_curr = adjM[curr].back();
                adjM[curr].pop_back();
                curr_st.push(next_curr);
            }
            else
            {
                path.push_back(curr);
                curr_st.pop();
            }
        }
        reverse(path.begin(), path.end());

        vector<vector<int>> ans;
        for (int i = 1; i < path.size(); i++)
        {
            ans.push_back({path[i - 1], path[i]});
        }

        return ans;
    }
};