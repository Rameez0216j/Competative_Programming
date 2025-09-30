// Solution : https://www.youtube.com/watch?v=yt6bi_g4C0I&t=345s
// ******************************************* My Solution *******************************************
/*
    Tips and Tricks:
        - In BFS Always use visited array based on state [here {currRow,currCol,keysStatus}]
*/
class Solution
{
public:
    int solveBFS(vector<string> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int maxKeyStatus = 0;
        int startRow, startCol;

        // find maxKeyStatus
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
                {
                    int key = grid[i][j] - 'a';
                    maxKeyStatus = maxKeyStatus | (1 << key);
                }

                if (grid[i][j] == '@')
                {
                    startRow = i;
                    startCol = j;
                }
            }
        }

        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(maxKeyStatus, false)));
        visited[startRow][startCol][0] = true; // marked starting position as visited

        queue<vector<int>> q;
        q.push({startRow, startCol, 0}); //{stRow,stCol,keyStatus}
        int steps = 0;
        while (!q.empty())
        {
            int s = q.size();
            while (s--)
            {
                int currRow = q.front()[0];
                int currCol = q.front()[1];
                int currKeyStatus = q.front()[2];
                q.pop();

                // Obtained all Keys
                if (currKeyStatus == maxKeyStatus)
                    return steps;

                int r[] = {1, -1, 0, 0};
                int c[] = {0, 0, -1, 1};

                for (int i = 0; i < 4; i++)
                {
                    int newRow = currRow + r[i];
                    int newCol = currCol + c[i];

                    if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m && grid[newRow][newCol] != '#' && !visited[newRow][newCol][currKeyStatus])
                    {
                        int newKeyStatus = currKeyStatus;

                        // Process Keys and Locks
                        if (grid[newRow][newCol] >= 'a' && grid[newRow][newCol] <= 'f')
                        {
                            int key = grid[newRow][newCol] - 'a';
                            newKeyStatus = currKeyStatus | (1 << key);
                        }
                        else if (grid[newRow][newCol] >= 'A' && grid[newRow][newCol] <= 'F')
                        {
                            int lock = grid[newRow][newCol] - 'A';
                            bool keyAvailable = currKeyStatus & (1 << lock);
                            if (!keyAvailable)
                                continue;
                        }

                        visited[newRow][newCol][newKeyStatus] = true;
                        q.push({newRow, newCol, newKeyStatus});
                    }
                }
            }
            steps++;
        }
        return -1;
    }

    int shortestPathAllKeys(vector<string> &grid)
    {
        return solveBFS(grid);
    }
};
// ******************************************* My Solution *******************************************

// ******************************** My Solution [Cleaned and Improved] ********************************
/*
class Solution {
    public:
    struct State {
        int row, col, mask;  // position + collected keys bitmask
    };

    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int totalKeys = 0;
        int startRow = 0, startCol = 0;

        // Step 1: Find starting point and total number of keys
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    startRow = i;
                    startCol = j;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    totalKeys = max(totalKeys, grid[i][j] - 'a' + 1);
                }
            }
        }

        int finalMask = (1 << totalKeys) - 1;  // e.g., 3 keys => mask 0b111

        // visited[row][col][mask] = already visited with this key set
        vector<vector<vector<bool>>> visited(
            n, vector<vector<bool>>(m, vector<bool>(1 << totalKeys, false))
        );

        queue<State> q;
        q.push({startRow, startCol, 0});
        visited[startRow][startCol][0] = true;

        int steps = 0;
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        // Step 2: BFS
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [row, col, mask] = q.front();
                q.pop();

                // All keys collected
                if (mask == finalMask) return steps;

                for (int k = 0; k < 4; k++) {
                    int nr = row + dr[k];
                    int nc = col + dc[k];
                    int newMask = mask;

                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                    char cell = grid[nr][nc];
                    if (cell == '#') continue;  // wall

                    // Key
                    if (cell >= 'a' && cell <= 'f') {
                        newMask |= (1 << (cell - 'a'));
                    }

                    // Lock
                    if (cell >= 'A' && cell <= 'F') {
                        if (!(mask & (1 << (cell - 'A')))) continue; // don't have key
                    }

                    if (!visited[nr][nc][newMask]) {
                        visited[nr][nc][newMask] = true;
                        q.push({nr, nc, newMask});
                    }
                }
            }
            steps++;
        }

        return -1;  // Impossible
    }
};
*/
// ******************************** My Solution [Cleaned and Improved] ********************************