// ***************************************************** My Solution *****************************************************
class Solution {
    int mod = 1e9 + 7;

    public:
    int solveRec(int row, int col, vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<int> r = {1, -1, 0, 0};
        vector<int> c = {0, 0, 1, -1};

        long long ans = 1; // path with only this cell
        for (int i = 0; i < 4; i++) {
            int next_row = row + r[i];
            int next_col = col + c[i];
            if (next_row >= 0 && next_col >= 0 && next_row < n && next_col < m 
                && grid[row][col] < grid[next_row][next_col]) {
                ans = (ans + solveRec(next_row, next_col, grid)) % mod;
            }
        }
        return ans;
    }

    int solveRec_Mem(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &dp) {
        int n = grid.size();
        int m = grid[0].size();

        if (dp[row][col] != -1) return dp[row][col];

        vector<int> r = {1, -1, 0, 0};
        vector<int> c = {0, 0, 1, -1};

        long long ans = 1; // path with only this cell
        for (int i = 0; i < 4; i++) {
            int next_row = row + r[i];
            int next_col = col + c[i];
            if (next_row >= 0 && next_col >= 0 && next_row < n && next_col < m 
                && grid[row][col] < grid[next_row][next_col]) {
                ans = (ans + solveRec_Mem(next_row, next_col, grid, dp)) % mod;
            }
        }
        return dp[row][col] = ans;
    }

    int countPaths(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        // Since the sequence is always increasing (strictly) there is no chance of cycles so no need of visited array

        // TC for solveRec: Exponential in worst case (no memoization)
        // TC for solveRec_Mem: O(n*m)
        // SC for solveRec_Mem: O(n*m) for dp + O(n*m) recursion stack
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Recursion
                // ans = (ans + solveRec(i, j, grid)) % mod;

                // Recursion + Memoization
                ans = (ans + solveRec_Mem(i, j, grid, dp)) % mod;
            }
        }
        return ans;
    }
};
// ***************************************************** My Solution *****************************************************
