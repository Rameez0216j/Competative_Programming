// Solution : https://www.youtube.com/watch?v=lvUte5NcTJ4
// ****************************** My Solution ******************************
class Solution {
    public:
    int solveRec(int ind,int mask,vector<int> &uniqueVals,unordered_map<int,vector<int>> &valRows){
        int n=uniqueVals.size();
        if(ind==n) return 0;

        int ans=solveRec(ind+1,mask,uniqueVals,valRows); // skip curr Val
        for(int row : valRows[uniqueVals[ind]]){
            bool isUsed=mask&(1<<row);
            if(!isUsed){
                int new_mask = mask | (1<<row);
                ans=max(ans,uniqueVals[ind]+solveRec(ind+1,new_mask,uniqueVals,valRows));
            } 
        }
        
        return ans;
    }


    int solveRec_Mem(int ind,int mask,vector<int> &uniqueVals,unordered_map<int,vector<int>> &valRows,vector<vector<int>> &dp){
        int n=uniqueVals.size();
        if(ind==n) return 0;
        
        if(dp[ind][mask]!=-1) return dp[ind][mask];

        int ans=solveRec_Mem(ind+1,mask,uniqueVals,valRows,dp); // skip curr Val
        for(int row : valRows[uniqueVals[ind]]){
            bool isUsed=mask&(1<<row);
            if(!isUsed){
                int new_mask = mask | (1<<row);
                ans=max(ans,uniqueVals[ind]+solveRec_Mem(ind+1,new_mask,uniqueVals,valRows,dp));
            } 
        }
        
        return dp[ind][mask]=ans;
    }


    int maxScore(vector<vector<int>>& grid) {
        // Here we take rows as mask as they needed to be select only once ==> select -> 1, not select -> 0 (10 in count ==> 2^11)
        unordered_set<int> s;
        unordered_map<int,vector<int>> valRows; // [val ===> rows]

        int n=grid.size();
        int m=grid[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                s.insert(grid[i][j]);
                valRows[grid[i][j]].push_back(i);
            }
        }

        vector<int> uniqueVals(s.begin(),s.end());


        // Recursion
        // return solveRec(0,0,uniqueVals,valRows);



        // Recursion + Memoization ==> TC(number of states) = TC(100*2^11) ==> Worst case
        vector<vector<int>> dp(uniqueVals.size()+1,vector<int>(pow(2,11),-1));
        return solveRec_Mem(0,0,uniqueVals,valRows,dp);
    }
};
// ****************************** My Solution ******************************







// ****************************** My Solution [Notes with comments] ******************************
/*
class Solution {
    public:

    // Recursive function to compute max score
    // ind → current index in uniqueVals vector
    // mask → bitmask of selected rows (bit i is set if row i is already used)
    // uniqueVals → all unique values from the grid
    // valRows → mapping from value → rows it appears in
    int solveRec(int ind, int mask, vector<int> &uniqueVals, unordered_map<int, vector<int>> &valRows) {
        int n = uniqueVals.size();
        
        // Base case: all values have been considered
        if (ind == n) return 0;

        // Option 1: Skip current value
        int ans = solveRec(ind + 1, mask, uniqueVals, valRows);

        // Option 2: Try to select this value from a row that hasn't been used yet
        for (int row : valRows[uniqueVals[ind]]) {
            bool isUsed = mask & (1 << row); // check if row is already used
            if (!isUsed) {
                int new_mask = mask | (1 << row); // mark row as used
                // Take current value + solve for rest
                ans = max(ans, uniqueVals[ind] + solveRec(ind + 1, new_mask, uniqueVals, valRows));
            }
        }

        return ans;
    }

    // Same as solveRec, but with memoization (DP)
    int solveRec_Mem(int ind, int mask, vector<int> &uniqueVals,
                     unordered_map<int, vector<int>> &valRows,
                     vector<vector<int>> &dp) {
        int n = uniqueVals.size();
        
        // Base case
        if (ind == n) return 0;
        
        // If already computed, return cached value
        if (dp[ind][mask] != -1) return dp[ind][mask];

        // Option 1: Skip current value
        int ans = solveRec_Mem(ind + 1, mask, uniqueVals, valRows, dp);

        // Option 2: Try placing current value in one of its rows if row is unused
        for (int row : valRows[uniqueVals[ind]]) {
            bool isUsed = mask & (1 << row);
            if (!isUsed) {
                int new_mask = mask | (1 << row);
                ans = max(ans, uniqueVals[ind] + solveRec_Mem(ind + 1, new_mask, uniqueVals, valRows, dp));
            }
        }

        // Store and return result
        return dp[ind][mask] = ans;
    }

    int maxScore(vector<vector<int>>& grid) {
        // We’ll use row usage as a bitmask (only one cell per row allowed)
        // There can be at most 11 rows (as per constraint), so 2^11 = 2048 possible masks

        unordered_set<int> s; // to collect unique values
        unordered_map<int, vector<int>> valRows; // maps each value to the list of rows it appears in

        int n = grid.size();
        int m = grid[0].size();

        // Populate the value→rows map and collect unique values
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                s.insert(grid[i][j]);
                valRows[grid[i][j]].push_back(i);
            }
        }

        vector<int> uniqueVals(s.begin(), s.end()); // get all unique values

        // ----------- Recursion Only (Exponential) ------------
        // return solveRec(0, 0, uniqueVals, valRows);

        // ----------- Recursion + Memoization -----------------
        // State: dp[ind][mask] where:
        // ind → index in uniqueVals
        // mask → bitmask representing used rows
        // Total states = uniqueVals.size() * 2^n (n ≤ 11)
        vector<vector<int>> dp(uniqueVals.size() + 1, vector<int>(1 << 11, -1));

        return solveRec_Mem(0, 0, uniqueVals, valRows, dp);
    }
};
*/
// ****************************** My Solution [Notes with comments] ******************************