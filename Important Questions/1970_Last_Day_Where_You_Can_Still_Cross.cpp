// *********************************** My Solution [DSU] ***********************************
/*
    ---------------------------------------------
    🧩 NOTE: Handling the Variant of the Problem
    ---------------------------------------------

    If the problem states that **not all cells will eventually be flooded**, 
    it means some cells are **permanent land cells** — they will never turn into water.

    In that case, we should first handle these permanent lands separately before
    doing the normal reverse-day DSU simulation.

    Here’s the step-by-step idea:

    1️⃣ Mark all flooded cells as water (1), and keep other cells as permanent land (0).

    2️⃣ Using DSU (Disjoint Set Union):
        - Connect all **adjacent permanent land cells** (up, down, left, right).
        - Connect any land cell in the **top row** to the virtual TOP node.
        - Connect any land cell in the **bottom row** to the virtual BOTTOM node.

    3️⃣ After building this DSU, check:
        - If the **TOP** and **BOTTOM** nodes are already connected, 
        it means there exists a continuous land path from top to bottom
        using only the permanent lands.

        - In that scenario, you can **always cross**, no matter how many days pass.
        Hence, directly return the maximum possible day value 
        (rows * cols), representing that crossing is always possible.

    4️⃣ Otherwise:
        - Proceed with the **standard reverse DSU process** (as in LeetCode 1970):
        Start from the last day, convert flooded cells back to land one by one in reverse order,
        and check when the top and bottom rows get connected.
        The first day (in reverse) when they connect gives the answer.

    ---------------------------------------------
    🧠 Summary:
    ---------------------------------------------
    ✔ Permanent land → check connectivity first (if connected → always crossable).
    ✔ Otherwise → perform reverse simulation (standard method).
    ---------------------------------------------
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

        // Always attach smaller tree to larger tree
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
        DisjointSet dsu(rows * cols + 2); // +2 for virtual top & bottom nodes

        vector<vector<int>> grid(rows, vector<int>(cols, 1)); // 1 = water, 0 = land
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        for (int day = rows * cols - 1; day >= 0; --day) {
            int r = cells[day][0] - 1;
            int c = cells[day][1] - 1;
            grid[r][c] = 0; // turn water -> land

            int cellId = r * cols + c;

            // Connect with adjacent land cells
            for (auto& dir : directions) {
                int newRow = r + dir[0];
                int newCol = c + dir[1];

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 0) {
                    int neighborId = newRow * cols + newCol;
                    dsu.unionSets(cellId, neighborId);
                }
            }

            // Connect with virtual nodes
            if (r == 0) dsu.unionSets(cellId, TOP_NODE);
            if (r == rows - 1) dsu.unionSets(cellId, BOTTOM_NODE);

            // Check if top and bottom are connected
            if (dsu.areConnected(TOP_NODE, BOTTOM_NODE)) return day;
        }

        return 0;
    }
};
// *********************************** My Solution [DSU] ***********************************







// Solution : https://www.youtube.com/watch?v=U4C7-PF_fi8
// **************************** My Solution [BFS + Binary Search] ****************************
/*
class Solution {
    public:
    // Performs BFS to check if there is a valid path from top to bottom
    bool canReachBottom(int startRow, int startCol, vector<vector<int>> &grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();

        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({startRow, startCol});
        visited[startRow][startCol] = true;

        while (!bfsQueue.empty()) {
            auto [row, col] = bfsQueue.front();
            bfsQueue.pop();

            // Reached bottom row
            if (row == numRows - 1) return true;

            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;

                if (newRow >= 0 && newRow < numRows &&
                    newCol >= 0 && newCol < numCols &&
                    !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                    visited[newRow][newCol] = true;
                    bfsQueue.push({newRow, newCol});
                }
            }
        }
        return false;
    }

    // Checks if crossing is possible on a given day
    bool canCrossOnDay(int numRows, int numCols, int day, vector<vector<int>> &floodCells) {
        vector<vector<int>> grid(numRows, vector<int>(numCols, 0));

        // Mark flooded cells up to the given day
        for (int i = 0; i < day; i++) {
            int r = floodCells[i][0] - 1;
            int c = floodCells[i][1] - 1;
            grid[r][c] = 1;
        }

        // Try starting from every land cell in the top row
        for (int col = 0; col < numCols; col++) {
            if (grid[0][col] == 0 && canReachBottom(0, col, grid))
                return true;
        }
        return false;
    }

    // Binary search for the latest day to cross
    int latestDayToCross(int numRows, int numCols, vector<vector<int>> &floodCells) {
        int low = 1, high = numRows * numCols;
        int latestPossibleDay = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canCrossOnDay(numRows, numCols, mid, floodCells)) {
                latestPossibleDay = mid;
                low = mid + 1; // Try for a later day
            } else {
                high = mid - 1; // Try an earlier day
            }
        }

        return latestPossibleDay;
    }
};
*/
// **************************** My Solution [BFS + Binary Search] ****************************