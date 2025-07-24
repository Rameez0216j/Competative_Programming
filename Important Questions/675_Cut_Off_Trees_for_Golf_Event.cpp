// Solution : https://www.youtube.com/watch?v=g3RpN03vo0g
// ********************************************** My Solution **********************************************
/*
    Problem Understanding - Leetcode 675: Cut Off Trees for Golf Event

    ✅ Objective:
    - You start at position (0, 0) in a 2D grid (forest).
    - Each cell:
        - 0: Impassable (cannot walk)
        - 1: Empty cell (can walk)
        - >1: Tree with specific height (can walk & must cut)
    - You must cut all trees in **increasing order of their height**.
    - You can walk in 4 directions (up, down, left, right), one step per unit time.

    ✅ Key Insights:
    - You are allowed to walk on any cell with value > 0 (i.e., walkable).
    - While walking, you can pass through:
        - Trees already cut
        - Trees not yet cut
        - Trees taller than the one you're about to cut
    - So, the **height of the cell you're walking to doesn't matter at all** for movement.
    - The only height that matters is the order in which you cut the trees (sorted by value).

    ✅ Mistake to Avoid:
    - ❌ Do NOT write: forest[curr][col] <= forest[new][col] in BFS (findDist) as below
    if( new_row >= 0 && new_row < n && new_col >= 0 && new_col < m &&
        forest[new_row][new_col] != 0 && !visited[new_row][new_col] &&
        forest[curr][col] <= forest[new][col])

      This wrongly restricts movement to equal or taller trees and blocks valid paths.
    - ✅ Instead, just ensure: forest[new][col] != 0

    ✅ Movement Validity:
    - A cell is valid to move into if:
        - It’s inside bounds
        - It’s not 0
        - It hasn’t been visited yet

    ✅ Strategy:
    1. Extract all tree cells with value > 1.
    2. Sort them by height in ascending order.
    3. Use BFS from current position to the next target tree.
    4. Accumulate the distance (steps) to reach and cut all trees.
    5. If any tree is unreachable, return -1.
*/

class Solution {
    public:
    int findDist(pair<int,pair<int,int>> &src, pair<int,pair<int,int>> &dest, vector<vector<int>>& forest) {
        int n = forest.size();
        int m = forest[0].size();
        int dest_row = dest.second.first;
        int dest_col = dest.second.second;

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<int,int>> q;
        q.push(src.second);
        visited[src.second.first][src.second.second] = true;

        int dist = 0;
        vector<int> r = {1, -1, 0, 0};
        vector<int> c = {0, 0, 1, -1};

        while (!q.empty()) {
            int len = q.size();
            while (len--) {
                int curr_row = q.front().first;
                int curr_col = q.front().second;
                q.pop();

                if (curr_row == dest_row && curr_col == dest_col) return dist;

                for (int i = 0; i < 4; ++i) {
                    int new_row = curr_row + r[i];
                    int new_col = curr_col + c[i];

                    if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m &&
                        forest[new_row][new_col] != 0 && !visited[new_row][new_col]) {
                        visited[new_row][new_col] = true;
                        q.push({new_row, new_col});
                    }
                }
            }
            dist++;
        }
        return -1; // unreachable
    }

    int cutOffTree(vector<vector<int>>& forest) {
        int n = forest.size();
        int m = forest[0].size();
        vector<pair<int, pair<int, int>>> cells;

        // Add all trees
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (forest[i][j] > 1)
                    cells.push_back({forest[i][j], {i, j}});
            }
        }

        // Sort by tree height
        sort(cells.begin(), cells.end());

        // Add starting point at (0, 0)
        pair<int, pair<int, int>> start = {0, {0, 0}};
        int totalDist = 0;

        for (int i = 0; i < cells.size(); ++i) {
            int dist = findDist(start, cells[i], forest);
            if (dist == -1) return -1;
            totalDist += dist;
            start = cells[i]; // move to next source
        }

        return totalDist;
    }
};
// ********************************************** My Solution **********************************************





// ********************************************** My Solution [Professional] **********************************************
/*
class Solution {
public:
    // Direction vectors for movement: up, down, left, right
    const vector<int> dirRow = {-1, 1, 0, 0};
    const vector<int> dirCol = {0, 0, -1, 1};

    // BFS to find the shortest distance from src to dest
    int bfs(const vector<vector<int>>& forest, pair<int, int> src, pair<int, int> dest) {
        if (src == dest) return 0;

        int rows = forest.size();
        int cols = forest[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int, int>> q;

        q.push(src);
        visited[src.first][src.second] = true;
        int steps = 0;

        while (!q.empty()) {
            int qSize = q.size();
            while (qSize--) {
                auto [currRow, currCol] = q.front();
                q.pop();

                if (currRow == dest.first && currCol == dest.second)
                    return steps;

                for (int d = 0; d < 4; ++d) {
                    int newRow = currRow + dirRow[d];
                    int newCol = currCol + dirCol[d];

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                        forest[newRow][newCol] != 0 && !visited[newRow][newCol]) {
                        visited[newRow][newCol] = true;
                        q.push({newRow, newCol});
                    }
                }
            }
            ++steps;
        }

        return -1; // Destination is unreachable
    }

    int cutOffTree(vector<vector<int>>& forest) {
        int rows = forest.size();
        int cols = forest[0].size();

        // Collect all tree cells (value > 1) with their positions
        vector<tuple<int, int, int>> trees;  // {height, row, col}
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (forest[i][j] > 1) {
                    trees.emplace_back(forest[i][j], i, j);
                }
            }
        }

        // Sort trees by increasing height
        sort(trees.begin(), trees.end());

        // Start BFS from (0, 0)
        pair<int, int> currPos = {0, 0};
        int totalSteps = 0;

        for (const auto& [height, row, col] : trees) {
            int steps = bfs(forest, currPos, {row, col});
            if (steps == -1) return -1;
            totalSteps += steps;
            currPos = {row, col};  // Move to the new position
        }

        return totalSteps;
    }
};
*/
// ********************************************** My Solution [Professional] **********************************************