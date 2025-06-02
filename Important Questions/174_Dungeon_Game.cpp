// Solution (Most Important) : https://www.youtube.com/watch?v=Mlcy-9hB6Jc&t=2192s
// ******************************************** My Solution [DP] ********************************************
class Solution {
    public:
    int explore(int row,int col,vector<vector<int>>& dungeon){
        if(row>=dungeon.size() || col>=dungeon[0].size()) return INT_MAX;

        // The below snippet tells how much health you need to stand out without diying at current cell (Queen cell)
        if(row==(dungeon.size()-1) && col==(dungeon[0].size()-1)){
            if(dungeon[row][col]<0) return abs(dungeon[row][col])+1; // +1 for minimum health after damage 
            else return 1; 
        }

        int right=explore(row+1,col,dungeon);
        int down=explore(row,col+1,dungeon);

        // ans ---> minimum helath needed to survive current cell while coming from other cells
        int ans = min(right,down) - dungeon[row][col];
        return ans>0 ? ans : 1;
    }


    int exploreMem(int row,int col,vector<vector<int>>& dungeon,vector<vector<int>> &dp){
        if(row>=dungeon.size() || col>=dungeon[0].size()) return INT_MAX;

        if(dp[row][col]!=-1) return dp[row][col];

        // The below snippet tells how much health you need to stand out without diying at current cell (Queen cell)
        if(row==(dungeon.size()-1) && col==(dungeon[0].size()-1)){
            if(dungeon[row][col]<0) return abs(dungeon[row][col])+1; // +1 for minimum health after damage 
            else return 1; 
        }

        int right=exploreMem(row+1,col,dungeon,dp);
        int down=exploreMem(row,col+1,dungeon,dp);

        // ans ---> minimum helath needed to survive current cell while coming from other cells
        int ans = min(right,down) - dungeon[row][col];
        return dp[row][col]=ans>0 ? ans : 1;
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // Recursion 
        // return explore(0,0,dungeon);


        // Recursion + Memoization
        int n=dungeon.size();
        int m=dungeon[0].size();
        vector<vector<int>> dp(n,vector<int>(m,-1));
        return exploreMem(0,0,dungeon,dp);
    }
};
// ******************************************** My Solution [DP] ********************************************