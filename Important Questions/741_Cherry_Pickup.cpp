// ************************************ My Solution [DP] - Two travellers approach ************************************
class Solution {
    public:
    // Two travellers approach
    int solveRec(int r1,int c1,int r2,int c2,vector<vector<int>>& grid){
        int n=grid.size();
        int m=grid[0].size();
        if(r1>=n || c1>=m || r2>=n || c2>=m || grid[r1][c1]==-1 || grid[r2][c2]==-1) return INT_MIN;
        
        // When r1==n-1 && c1==m-1 then automatically r2==n-1 && c2==m-1
        if(r1==n-1 && c1==m-1) return grid[r1][c1];

        int ans=0;
        // if both are at same block then consider only once
        if(r1==r2 && c1==c2) ans=grid[r1][c1];
        else ans=grid[r1][c1]+grid[r2][c2];

        // Wrong logic (as only one player is moving)
        // int down1=solveRec(r1+1,c1,r2,c2,grid);
        // int down2=solveRec(r1,c1+1,r2,c2,grid);
        // int right1=solveRec(r1,c1,r2+1,c2,grid);
        // int right2=solveRec(r1,c1,r2,c2+1,grid);
        // return ans+max({down1,down2,right1,right2});


        // Possible movements
        int case1=solveRec(r1+1,c1,r2+1,c2,grid);
        int case2=solveRec(r1+1,c1,r2,c2+1,grid);
        int case3=solveRec(r1,c1+1,r2+1,c2,grid);
        int case4=solveRec(r1,c1+1,r2,c2+1,grid);
        int nextSol=max({case1,case2,case3,case4});
        if(nextSol==INT_MIN) return INT_MIN;
        return ans+nextSol;
    }


    int solveRecMem(int r1,int c1,int r2,int c2,vector<vector<int>>& grid,vector<vector<vector<vector<int>>>> &dp){
        int n=grid.size();
        int m=grid[0].size();
        if(r1>=n || c1>=m || r2>=n || c2>=m || grid[r1][c1]==-1 || grid[r2][c2]==-1) return INT_MIN;
        
        // When r1==n-1 && c1==m-1 then automatically r2==n-1 && c2==m-1
        if(r1==n-1 && c1==m-1) return grid[r1][c1];


        if(dp[r1][c1][r2][c2]!=-1) return dp[r1][c1][r2][c2];

        int ans=0;
        // if both are at same block then consider only once
        if(r1==r2 && c1==c2) ans=grid[r1][c1];
        else ans=grid[r1][c1]+grid[r2][c2];

        // Possible movements
        int case1=solveRecMem(r1+1,c1,r2+1,c2,grid,dp);
        int case2=solveRecMem(r1+1,c1,r2,c2+1,grid,dp);
        int case3=solveRecMem(r1,c1+1,r2+1,c2,grid,dp);
        int case4=solveRecMem(r1,c1+1,r2,c2+1,grid,dp);
        int nextSol=max({case1,case2,case3,case4});

        // Method 1
        // if(nextSol==INT_MIN) return dp[r1][c1][r2][c2]=INT_MIN;
        // return dp[r1][c1][r2][c2]=ans+nextSol;

        return dp[r1][c1][r2][c2]= nextSol==INT_MIN ? INT_MIN : ans+nextSol;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        // Recursion
        // int ans=solveRec(0,0,0,0,grid);
        // return ans==INT_MIN ? 0 : ans;


        // Recursion + Memoization 
        int n=grid.size();
        vector<vector<vector<vector<int>>>> dp(n,vector<vector<vector<int>>>(n,vector<vector<int>>(n,vector<int>(n,-1))));
        int ans=solveRecMem(0,0,0,0,grid,dp);
        return ans==INT_MIN ? 0 : ans;
    }
};
// ************************************ My Solution [DP] - Two travellers approach ************************************




// ************************************ My Solution [2 way traversal] ************************************
/*
class Solution {
    int cherryPickup(vector<vector<int>>& grid) {

    }
};
*/
// ************************************ My Solution [2 way traversal] ************************************