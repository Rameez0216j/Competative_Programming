// ********************************* My Solution *********************************
/*
    Validate seating mask for current row:

    1. Check if all 1s in the current mask are on valid seats (i.e., not broken).
       → (mask & filterMask) == mask ensures that all seated positions in mask 
         are allowed in filterMask.

       Equivalent logic (also correct):
       if ((mask | filterMask) != filterMask) continue;

       Example:
         filterMask = 0b1011 → valid seats at positions 0, 1, and 3
         mask       = 0b0011 → wants to sit at 0 and 1 → OK
         mask       = 0b1100 → wants to sit at 2 and 3 → Invalid (seat 2 is blocked)


    2. Check that no two students sit adjacent to each other in the same row.
       → Adjacent students will be detected if any bit in `mask` is next to another 1-bit.

       Bit trick:
       if ((mask & (mask >> 1)) != 0) continue;

       Example:
         mask       = 0b0110 (students at seat 1 and 2) → Adjacent → Invalid
         mask >> 1  = 0b0011
         &          = 0b0010 → non-zero ⇒ invalid


    3. Check no student in current row is sitting diagonally adjacent to a student in the previous row.
       → Cheating diagonally must be prevented.

       Bit trick:
       if ((mask & (prevRowMask << 1)) != 0 || (mask & (prevRowMask >> 1)) != 0) continue;

       Explanation:
         - (prevRowMask << 1): simulates upper-left diagonal from previous row
         - (prevRowMask >> 1): simulates upper-right diagonal from previous row
         - Any overlap with current mask indicates cheating risk

       Example:
         prevRowMask         = 0b0101 (students at seats 0 and 2)
         prevRowMask << 1    = 0b1010
         prevRowMask >> 1    = 0b0010

         mask                = 0b0010 (student at seat 1)
         mask & (prev << 1)  = 0     → no left diagonal conflict
         mask & (prev >> 1)  = 0b0010 → right diagonal conflict ⇒ invalid
*/

class Solution {
    public:
    int n, m;

    // Generate all valid seatings for the current row based on previous row's mask
    vector<vector<int>> getValidSeatings(int prevRowMask, vector<int>& currRow) {
        int filterMask = 0;
        for (int i = 0; i < m; i++) {
            filterMask |= (currRow[i] << i);
        }

        unordered_set<int> validMasks;

        // Generate all masks for this row
        for (int mask = 0; mask < (1 << m); mask++) {
            // Check if all 1s in mask are allowed seats in current row

            // if ((mask | filterMask) != filterMask) continue; // this is also correct
            if ((mask & filterMask) != mask) continue;

            // No adjacent students
            if ((mask & (mask >> 1)) != 0) continue;

            // No cheating with previous row (diagonally)
            if ((mask & (prevRowMask << 1)) != 0 || (mask & (prevRowMask >> 1)) != 0) continue;

            validMasks.insert(mask);
        }

        // Convert valid masks to vector form
        vector<vector<int>> validSeatings;
        for (int mask : validMasks) {
            vector<int> seating(m, 0);
            for (int i = 0; i < m; i++) {
                if ((mask >> i) & 1) seating[i] = 1;
            }
            validSeatings.push_back(seating);
        }

        return validSeatings;
    }

    int solveRec(int row, int prevRowMask, vector<vector<int>>& validSeat) {
        if (row == n) return 0;

        vector<vector<int>> validSeatings = getValidSeatings(prevRowMask, validSeat[row]);
        int ans = INT_MIN;

        for (auto& seating : validSeatings) {
            int currMask = 0, count = 0;
            for (int i = 0; i < m; i++) {
                if (seating[i]) {
                    currMask |= (1 << i);
                    count++;
                }
            }

            int res = solveRec(row + 1, currMask, validSeat);
            if (res != -1) ans = max(ans, count + res);
        }

        return ans == INT_MIN ? -1 : ans;
    }



    int solveRec_Mem(int row, int prevRowMask, vector<vector<int>>& validSeat,vector<vector<int>> &dp) {
        if (row == n) return 0;

        if(dp[row][prevRowMask]!=INT_MIN) return dp[row][prevRowMask];

        vector<vector<int>> validSeatings = getValidSeatings(prevRowMask, validSeat[row]);
        int ans = INT_MIN;

        for (auto& seating : validSeatings) {
            int currMask = 0, count = 0;
            for (int i = 0; i < m; i++) {
                if (seating[i]) {
                    currMask |= (1 << i);
                    count++;
                }
            }

            int res = solveRec_Mem(row + 1, currMask, validSeat,dp);
            if (res != -1) ans = max(ans, count + res);
        }

        return dp[row][prevRowMask]=ans == INT_MIN ? -1 : ans;
    }

    int maxStudents(vector<vector<char>>& seats) {
        n = seats.size();
        m = seats[0].size();

        vector<vector<int>> validSeat(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                validSeat[i][j] = (seats[i][j] == '.') ? 1 : 0;
            }
        }


        // Recursion
        // return solveRec(0, 0, validSeat);


        // Recursion + Memoization
        vector<vector<int>> dp(n+1,vector<int>(1<<m,INT_MIN));
        return solveRec_Mem(0, 0, validSeat,dp);
    }
};
// ********************************* My Solution *********************************