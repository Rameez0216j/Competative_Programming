// Solution : https://www.youtube.com/watch?v=YZzJrQQP-Pk&t=1613s
// *********************************** My Solution [Prefix Sum + DP] Clean ***********************************
class Solution {
    int mod = 1e9 + 7;  // Define a modulo to avoid integer overflow in large results.

    public:

    // Helper function using recursion (no memoization version).
    int solveRec(int r1, int c1, int r2, int c2, int k, vector<vector<int>> &prefixPizza) {
        // Base case: if k == 1, this is the last piece. Return 1 if it contains at least one apple.
        if (k == 1) return 1;

        // Total apples in the subgrid (r1,c1) to (r2,c2) using prefix sum.
        int totalApples = prefixPizza[r2][c2] - prefixPizza[r1 - 1][c2] - prefixPizza[r2][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
        int ans = 0;

        // Try horizontal cuts between rows [r1...r2-1]
        for (int i = r1; i < r2; i++) {
            int up = prefixPizza[i][c2] - prefixPizza[r1 - 1][c2] - prefixPizza[i][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
            int down = totalApples - up;
            if (up >= 1 && down >= k - 1) {
                int next = solveRec(i + 1, c1, r2, c2, k - 1, prefixPizza); // Correctly cut from i+1 down
                ans = (ans % mod + next % mod) % mod;
            }
        }

        // Try vertical cuts between columns [c1...c2-1]
        for (int i = c1; i < c2; i++) {
            int left = prefixPizza[r2][i] - prefixPizza[r1 - 1][i] - prefixPizza[r2][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
            int right = totalApples - left;
            if (left >= 1 && right >= k - 1) {
                int next = solveRec(r1, i + 1, r2, c2, k - 1, prefixPizza); // Correctly cut from i+1 rightward
                ans = (ans % mod + next % mod) % mod;
            }
        }
        return ans;
    }

    // Recursive + memoized version to avoid recomputation.
    int solveRecMem(int r1, int c1, int r2, int c2, int k, vector<vector<int>> &prefixPizza, vector<vector<vector<int>>> &dp) {
        if (k == 1) return 1;
        if (dp[r1][c1][k] != -1) return dp[r1][c1][k]; // Return cached result

        int totalApples = prefixPizza[r2][c2] - prefixPizza[r1 - 1][c2] - prefixPizza[r2][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
        int ans = 0;

        for (int i = r1; i < r2; i++) {
            int up = prefixPizza[i][c2] - prefixPizza[r1 - 1][c2] - prefixPizza[i][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
            int down = totalApples - up;
            if (up >= 1 && down >= k - 1) {
                int next = solveRecMem(i + 1, c1, r2, c2, k - 1, prefixPizza, dp);
                ans = (ans % mod + next % mod) % mod;
            }
        }

        for (int i = c1; i < c2; i++) {
            int left = prefixPizza[r2][i] - prefixPizza[r1 - 1][i] - prefixPizza[r2][c1 - 1] + prefixPizza[r1 - 1][c1 - 1];
            int right = totalApples - left;
            if (left >= 1 && right >= k - 1) {
                int next = solveRecMem(r1, i + 1, r2, c2, k - 1, prefixPizza, dp);
                ans = (ans % mod + next % mod) % mod;
            }
        }

        return dp[r1][c1][k] = ans;
    }

    int ways(vector<string>& pizza, int k) {
        int n = pizza.size();        // number of rows
        int m = pizza[0].size();     // number of columns

        // Construct 2D prefix sum array (1-based indexing)
        vector<vector<int>> prefixPizza(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                prefixPizza[i][j] = (pizza[i - 1][j - 1] == 'A' ? 1 : 0)
                                    + prefixPizza[i - 1][j]
                                    + prefixPizza[i][j - 1]
                                    - prefixPizza[i - 1][j - 1];
            }
        }

        // Memoization DP table: dp[r1][c1][k] = number of ways to cut (r1,c1) to (n,m) into k pieces
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));

        // Edge case: if the entire pizza doesn't have enough apples
        if (prefixPizza[n][m] < k) return 0;

        // Start recursion from top-left (1,1) to bottom-right (n,m)
        return solveRecMem(1, 1, n, m, k, prefixPizza, dp);
    }
};
// *********************************** My Solution [Prefix Sum + DP] Clean ***********************************