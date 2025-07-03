// **************************** My Solution [Recursion ==> TLE and Memoization ==> MLE] ****************************
/*
class Solution {
public:
    int solveRec(int sx, int sy, int tx, int ty){
        if(sx>tx || sy>ty) return false;
        if(sx==tx && sy==ty) return true;
        
        return solveRec(sx+sy,sy,tx,ty) || solveRec(sx,sy+sx,tx,ty);
    }

    int solveRec_Mem(int sx, int sy, int tx, int ty,vector<vector<int>> &dp){
        if(sx>tx || sy>ty) return false;
        if(sx==tx && sy==ty) return true;

        if(dp[sx][sy]!=-1) return dp[sx][sy];
        
        return dp[sx][sy]=solveRec_Mem(sx+sy,sy,tx,ty,dp) || solveRec_Mem(sx,sy+sx,tx,ty,dp);
    }

    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // Recursion 
        // return solveRec(sx,sy,tx,ty);

        // Recursion + Memoization
        vector<vector<int>> dp(tx+1,vector<int>(ty+1,-1));
        return solveRec_Mem(sx,sy,tx,ty,dp);
    }
};
*/
// **************************** My Solution [Recursion ==> TLE and Memoization ==> MLE] ****************************





// ************************************ My Solution (Greedy + Backwards Tracing) ************************************
class Solution {
public:
    // Function to determine if we can reach (tx, ty) from (sx, sy)
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        // Work backwards from (tx, ty) to (sx, sy)
        // We keep reducing the larger of tx or ty using modulo with the smaller
        while (tx > sx && ty > sy) {
            if (tx > ty) 
                tx %= ty; // Reversing operation: came from (tx - ty, ty)
            else 
                ty %= tx; // Reversing operation: came from (tx, ty - tx)
        }

        // Now either tx == sx or ty == sy
        // Case 1: tx == sx, check if we can reach sy from ty by repeated subtraction of sx
        if (tx == sx && ty >= sy) return (ty - sy) % sx == 0;

        // Case 2: ty == sy, check if we can reach sx from tx by repeated subtraction of sy
        if (ty == sy && tx >= sx) return (tx - sx) % sy == 0;

        // Final check: exact match
        return tx == sx && ty == sy;
    }
};
// ************************************ My Solution (Greedy + Backwards Tracing) ************************************
