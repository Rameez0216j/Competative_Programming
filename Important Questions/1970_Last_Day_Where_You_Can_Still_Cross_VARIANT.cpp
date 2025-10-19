/*
🔹 Problem Statement: Last Day Where You Can Still Cross (and its variant)

You are given a grid of size `rows × cols`, where each cell starts as land (0).
Each day, one cell becomes water (1), according to the given list `cells`.

Your task is to determine the **latest possible day** (maximum index) 
when it is still possible to cross from the **top row** to the **bottom row** 
by moving only through land cells (4-directionally connected).

-----------------------
Variant (Extended Case):
-----------------------
If the problem specifies that **not all cells will be flooded** (i.e., some remain permanent land),
then before simulating the days, check if there already exists a path 
from top to bottom using these permanent land cells. 
If such a path exists, it means you can always cross — return the maximum possible day.

Return:
  The latest day index (1-based) when crossing is still possible.

----------------------------------------
Constraints (same as LeetCode #1970):
----------------------------------------
1 ≤ rows, cols ≤ 2 * 10^4
1 ≤ rows * cols ≤ 2 * 10^4
cells.length == rows * cols
1 ≤ cells[i][0] ≤ rows
1 ≤ cells[i][1] ≤ cols
All cells[i] are distinct.

Approach:
---------
1️⃣ If there is permanent land (cells that never flood), 
    check if they connect the top row and bottom row using DSU.
    If yes → return maximum day (always crossable).

2️⃣ Otherwise, simulate days **in reverse**:
    - Start from the last day (when all flooded).
    - Convert each cell from water → land in reverse order.
    - Union adjacent land cells.
    - When top and bottom become connected, return that day.

Time Complexity:  O(R × C × α(R×C)) ≈ O(R×C)
Space Complexity: O(R × C)
*/

#define ALL(container) (container).begin(), (container).end()

struct DisjointSet {
    vector<int> parent, componentSize;

    DisjointSet(int n) {
        parent.resize(n);
        componentSize.assign(n, 1);
        iota(ALL(parent), 0);
    }

    int findParent(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findParent(parent[node]);
    }

    void unionSets(int u, int v) {
        int rootU = findParent(u);
        int rootV = findParent(v);

        if (rootU == rootV) return;

        if (componentSize[rootU] < componentSize[rootV])
            swap(rootU, rootV);

        parent[rootV] = rootU;
        componentSize[rootU] += componentSize[rootV];
    }

    bool areConnected(int u, int v) {
        return findParent(u) == findParent(v);
    }
};

class Solution {
public:
    int latestDayToCross(int rows, int cols, vector<vector<int>>& cells) {
        const int TOP_NODE = rows * cols;
        const int BOTTOM_NODE = rows * cols + 1;
        DisjointSet dsu(rows * cols + 2);

        vector<vector<int>> grid(rows, vector<int>(cols, 0)); // 0 = land, 1 = water
        for (auto& cell : cells)
            grid[cell[0] - 1][cell[1] - 1] = 1;

        vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};

        // Step 1️⃣ : Pre-check permanent land connectivity
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) { // permanent land
                    int cellId = r * cols + c;

                    for (auto& dir : directions) {
                        int newRow = r + dir[0];
                        int newCol = c + dir[1];
                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 0) {
                            int neighborId = newRow * cols + newCol;
                            dsu.unionSets(cellId, neighborId);
                        }
                    }

                    if (r == 0) dsu.unionSets(cellId, TOP_NODE);
                    if (r == rows - 1) dsu.unionSets(cellId, BOTTOM_NODE);
                }
            }
        }

        // If top & bottom already connected → always crossable
        if (dsu.areConnected(TOP_NODE, BOTTOM_NODE))
            return rows * cols; // maximum day (always crossable)

        // Step 2️⃣ : Reverse simulation for flood sequence
        for (int day = rows * cols - 1; day >= 0; --day) {
            int r = cells[day][0] - 1;
            int c = cells[day][1] - 1;
            grid[r][c] = 0; // convert to land
            int cellId = r * cols + c;

            for (auto& dir : directions) {
                int newRow = r + dir[0];
                int newCol = c + dir[1];
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 0) {
                    int neighborId = newRow * cols + newCol;
                    dsu.unionSets(cellId, neighborId);
                }
            }

            if (r == 0) dsu.unionSets(cellId, TOP_NODE);
            if (r == rows - 1) dsu.unionSets(cellId, BOTTOM_NODE);

            if (dsu.areConnected(TOP_NODE, BOTTOM_NODE))
                return day;
        }

        return 0;
    }
};
