// ****************************************** My solution ******************************************
/*
    🔷 What does prefixSum[i][j] represent?

    prefixSum[i][j] = Maximum number of complete levels **beneath** the apex (i, j) 
                      that can form a full pyramid made of 1s.

                      ➤ Total pyramid height = prefixSum[i][j] + 1
                      ➤ For each cell, the number of valid pyramids = prefixSum[i][j]

    ----------------------------------------------------------------

    🔸 Rules for forming a valid upright pyramid:
        - Cell (i, j) is the apex (must be 1)
        - Next level (i+1): must have 1s at (j-1, j, j+1)
        - Next level (i+2): must have 1s at (j-2, j-1, j, j+1, j+2)
        - And so on...

        Each level k below apex must have `2k + 1` continuous 1s
        centered at column j.

    ----------------------------------------------------------------

    🔍 Example : prefixSum[i][j] = 2 (Height = 3) [only represented for one cell i.e grid[i][j] as apex]  ==> here apex is grid[1][3]

        Grid view:
            0 0 0 0 0 0 0
            0 0 0 1 0 0 0   ← Level 0 (apex at (i, j))
            0 0 1 1 1 0 0   ← Level 1
            0 1 1 1 1 1 0   ← Level 2

        🔹 Level 1 has 3 1s
        🔹 Level 2 has 5 1s
        🔹 Total height = 3
        🔹 Valid pyramids formed:
            - Height 2 (Levels 0 and 1)
            - Height 3 (Levels 0, 1, and 2)


        🔹 pyramid count = 2

            Pyramid_1

            0 0 0 0 0 0 0
            0 0 0 p 0 0 0   ← Level 0 (apex at (1, 3))
            0 0 p p p 0 0   ← Level 1
            0 1 1 1 1 1 0   ← Level 2


            Pyramid_2

            0 0 0 0 0 0 0
            0 0 0 p 0 0 0   ← Level 0 (apex at (1, 3))
            0 0 p p p 0 0   ← Level 1
            0 p p p p p 0   ← Level 2

    ----------------------------------------------------------------

    ✅ Summary:
        - prefixSum[i][j] = max number of full levels possible below apex (i, j)
        - Number of valid pyramids with (i, j) as apex = prefixSum[i][j]
        - Total pyramids = ∑ prefixSum[i][j] over all (i, j)

    🧠 Tip: 
        - Use bottom-up DP for upright pyramids
        - Use top-down DP for inverted pyramids
        - Reuse the same prefixSum matrix by overwriting it in the second pass

*/

/*
class Solution {
    public:
    int countPyramids(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int totalPyramids = 0;

        // DP matrix to store max height of pyramid at each cell
        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        // 🔼 Count upright pyramids (apex at top)
        for (int i = rows - 1; i >= 0; --i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    dp[i][j] = -1; // mark unusable
                }
                else if (i == rows - 1 || j == 0 || j == cols - 1) {
                    dp[i][j] = 0; // edges can't form pyramid
                }
                else {
                    dp[i][j] = min({dp[i + 1][j - 1], dp[i + 1][j], dp[i + 1][j + 1]}) + 1;
                    totalPyramids += dp[i][j];
                }
            }
        }

        // 🔽 Count inverted pyramids (apex at bottom)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    dp[i][j] = -1;
                }
                else if (i == 0 || j == 0 || j == cols - 1) {
                    dp[i][j] = 0;
                }
                else {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]}) + 1;
                    totalPyramids += dp[i][j];
                }
            }
        }

        return totalPyramids;
    }
};
*/
// ****************************************** My solution ******************************************






// ****************************************** Editorial Solution [Rec+Mem] ******************************************
class Solution {
    public:
    // Function to compute max height of pyramid with apex at (row, col)
    int computePyramidHeight(vector<vector<int>>& grid, int row, int col, vector<vector<int>>& dp) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Base conditions:
        // - Out of grid boundary
        // - Current cell is 0
        // - Cannot form another level below
        if (row <rows && col>=0 && col<cols && grid[row][col] == 0) return -1;
        if (row >= rows - 1 || col <= 0 || col >= cols - 1) return 0;

        // Check memoized result
        if (dp[row][col] != -1) return dp[row][col];

        // Recursively get heights from next level
        int left  = computePyramidHeight(grid, row + 1, col - 1, dp);
        int mid   = computePyramidHeight(grid, row + 1, col,     dp);
        int right = computePyramidHeight(grid, row + 1, col + 1, dp);

        // Store minimum of three directions + current level
        return dp[row][col] = 1 + min({left, mid, right});
    }

    int countPyramids(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int totalPyramids = 0;

        // 🔼 Count upright pyramids
        vector<vector<int>> dp(rows, vector<int>(cols, -1));

        for (int row = 0; row < rows - 1; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 1) {
                    totalPyramids += computePyramidHeight(grid, row, col, dp);
                }
            }
        }

        // 🔽 Count inverted pyramids: flip vertically
        reverse(grid.begin(), grid.end());
        dp.assign(rows, vector<int>(cols, -1));  // reset dp

        for (int row = 0; row < rows - 1; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] == 1) {
                    totalPyramids += computePyramidHeight(grid, row, col, dp);
                }
            }
        }

        return totalPyramids;
    }
};

// ****************************************** Editorial Solution [Rec+Mem] ******************************************