// Solution : https://www.youtube.com/watch?v=3IomMslYOOY&t=2439s
// ************************************* My Solution *************************************
class Solution
{
public:
    int getXors(int node, int &time, int parent, vector<int> &inTime, vector<int> &outTime, vector<int> &xorNodes, vector<int> &nums, unordered_map<int, vector<int>> &adjL)
    {
        inTime[node] = time;
        time += 1;

        int curr_xor = nums[node]; // ✅ use nums value, not node index
        for (int nbr : adjL[node])
        {
            if (nbr != parent)
                curr_xor ^= getXors(nbr, time, node, inTime, outTime, xorNodes, nums, adjL);
        }

        xorNodes[node] = curr_xor;
        outTime[node] = time;
        time += 1;
        return curr_xor;
    }

    int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
    {
        unordered_map<int, vector<int>> adjL;
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }

        // tracking in and out time of nodes in DFS to find out whose ancestor is who
        int n = edges.size() + 1;
        vector<int> inTime(n, 0);
        vector<int> outTime(n, 0);
        vector<int> xorNodes(n, 0);

        int time = 0;
        int rootXor = getXors(0, time, -1, inTime, outTime, xorNodes, nums, adjL);
        int ans = INT_MAX;
        for (int i = 1; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int a, b, c;

                if (inTime[i] < inTime[j] && outTime[j] < outTime[i])
                {
                    // i ancestor of j
                    a = xorNodes[j];
                    b = xorNodes[i] ^ xorNodes[j];
                    c = rootXor ^ xorNodes[i];
                }
                else if (inTime[j] < inTime[i] && outTime[i] < outTime[j])
                {
                    // j ancestor of i
                    a = xorNodes[i];
                    b = xorNodes[j] ^ xorNodes[i];
                    c = rootXor ^ xorNodes[j];
                }
                else
                {
                    // disjoint
                    a = xorNodes[i];
                    b = xorNodes[j];
                    c = rootXor ^ xorNodes[i] ^ xorNodes[j];
                }

                int currMax = max({a, b, c});
                int currMin = min({a, b, c});
                ans = min(ans, currMax - currMin);
            }
        }

        return ans;
    }
};
// ************************************* My Solution *************************************