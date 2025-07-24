// Solution : https://www.youtube.com/watch?v=eagGLroZXMk
// ************************************ My Solution ************************************
class Solution {
    int ans = 0;

    public:
    void dfs(int count, int row, int col, int& totalCells, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Base case: reached ending square and visited all valid cells
        if (count == totalCells - 1 && grid[row][col] == 2) {
            ans++;
            return;
        }

        // Invalid end condition: reached end too early
        if (grid[row][col] == 2) return;

        // Mark cell as visited
        int prev = grid[row][col];
        grid[row][col] = -1;

        vector<int> dirRow = {0, 0, -1, 1};
        vector<int> dirCol = {-1, 1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int newRow = row + dirRow[i];
            int newCol = col + dirCol[i];

            if (newRow >= 0 && newRow < n &&
                newCol >= 0 && newCol < m &&
                grid[newRow][newCol] != -1) {
                dfs(count + 1, newRow, newCol, totalCells, grid);
            }
        }

        // Backtrack
        grid[row][col] = prev;
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int totalCells = 0;
        int startRow = 0, startCol = 0;

        // Count all non-obstacle cells and locate the start
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != -1) totalCells++;
                if (grid[i][j] == 1) {
                    startRow = i;
                    startCol = j;
                }
            }
        }

        dfs(0, startRow, startCol, totalCells, grid);
        return ans;
    }
};

// ************************************ My Solution ************************************