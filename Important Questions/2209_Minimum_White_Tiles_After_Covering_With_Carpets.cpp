// ************************************** My Solution **************************************
class Solution {
    public:
    int solveRec(int curr,string &floor, int numCarpets, int carpetLen){
        int n=floor.size();
        if(curr>=floor.size()) return 0;

        int placeCarpet=1e9;
        int skipTile=0;
        if(numCarpets>0) placeCarpet=solveRec(curr+carpetLen,floor,numCarpets-1,carpetLen);
        if(floor[curr]=='1'){
            skipTile=1+solveRec(curr+1,floor,numCarpets,carpetLen);
        }else skipTile=solveRec(curr+1,floor,numCarpets,carpetLen);

        return min(placeCarpet,skipTile);
    }


    int solveRec_Mem(int curr,string &floor, int numCarpets, int carpetLen,vector<vector<int>> &dp){
        int n=floor.size();
        if(curr>=floor.size()) return 0;

        if(dp[curr][numCarpets]!=-1) return dp[curr][numCarpets];

        int placeCarpet=1e9;
        int skipTile=0;
        if(numCarpets>0) placeCarpet=solveRec_Mem(curr+carpetLen,floor,numCarpets-1,carpetLen,dp);
        if(floor[curr]=='1'){
            skipTile=1+solveRec_Mem(curr+1,floor,numCarpets,carpetLen,dp);
        }else skipTile=solveRec_Mem(curr+1,floor,numCarpets,carpetLen,dp);

        return dp[curr][numCarpets]=min(placeCarpet,skipTile);
    }

    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        // Recursion
        // return solveRec(0,floor,numCarpets,carpetLen);


        // Recursion + Memoization
        vector<vector<int>> dp(floor.size()+1,vector<int>(numCarpets+1,-1));
        return solveRec_Mem(0,floor,numCarpets,carpetLen,dp);
    }
};
// ************************************** My Solution **************************************