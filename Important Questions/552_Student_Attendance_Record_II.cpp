// Solution : https://www.youtube.com/watch?v=hdI1wrNsc8A
// *********************************** My solution ***********************************
class Solution {
    int mod=1e9+7;
    public:
    int solveRec(int day, int late, int absents, int n) {
        if (late >= 3 || absents > 1) return 0; // Constraint violation
        if (day == n) return 1; // Valid sequence of n days

        // Case 1: Present today
        int case1 = solveRec(day + 1, 0, absents, n);
        
        // Case 2: Absent today
        int case2 = solveRec(day + 1, 0, absents + 1, n);
        
        // Case 3: Late today
        int case3 = solveRec(day + 1, late + 1, absents, n);

        return case1 + case2 + case3;
    }


    int solveRec_Mem(int day, int late, int absents, int n,vector<vector<vector<int>>> &dp) {
        if (late >= 3 || absents > 1) return 0; // Constraint violation
        if (day == n) return 1; // Valid sequence of n days

        if(dp[day][late][absents]!=-1) return dp[day][late][absents];

        // Case 1: Present today
        int case1 = solveRec_Mem(day + 1, 0, absents, n, dp);
        
        // Case 2: Absent today
        int case2 = solveRec_Mem(day + 1, 0, absents + 1, n, dp);
        
        // Case 3: Late today
        int case3 = solveRec_Mem(day + 1, late + 1, absents, n, dp);

        return dp[day][late][absents]=((case1%mod + case2%mod)%mod + case3%mod )%mod;
    }

    int checkRecord(int n) {
        // Recursion
        // return solveRec(0, 0, 0, n);


        // Recursion + Memoization
        vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(3,vector<int>(3,-1)));
        return solveRec_Mem(0, 0, 0, n,dp);
    }
};
// *********************************** My solution ***********************************
