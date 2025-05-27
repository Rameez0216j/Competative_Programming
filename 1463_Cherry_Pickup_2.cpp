// ************************************ My Solution [DP] - Two travellers approach ************************************
class Solution {
    public:
    // Two travellers approach
    int solveRec(int r,int c1,int c2,vector<vector<int>>& grid){
        int n=grid.size();
        int m=grid[0].size();
        if(r>n || c1<0 || c1>=m || c2<0 || c2>=m) return INT_MIN;
        if(r==n) return 0;
        

        int ans=0;
        // if both are at same block then consider only once
        if(c1==c2) ans=grid[r][c1];
        else ans=grid[r][c1]+grid[r][c2];

        // Possible movements
        int nextSol=INT_MIN;
        int c1Dir[]={1,1,1,0,0,0,-1,-1,-1};
        int c2Dir[]={1,-1,0,1,-1,0,1,-1,0};
        for(int i=0;i<9;i++){
            int newC1=c1+c1Dir[i];
            int newC2=c2+c2Dir[i];
            nextSol=max(nextSol,solveRec(r+1,newC1,newC2,grid));
        }

        return nextSol==INT_MIN ? INT_MIN : ans+nextSol;
    }



    int solveRecMem(int r,int c1,int c2,vector<vector<int>>& grid,vector<vector<vector<int>>> &dp){
        int n=grid.size();
        int m=grid[0].size();
        if(r>n || c1<0 || c1>=m || c2<0 || c2>=m) return INT_MIN;
        if(r==n) return 0;
        
        if(dp[r][c1][c2]!=-1) return dp[r][c1][c2];

        int ans=0;
        // if both are at same block then consider only once
        if(c1==c2) ans=grid[r][c1];
        else ans=grid[r][c1]+grid[r][c2];

        // Possible movements
        int nextSol=INT_MIN;
        int c1Dir[]={1,1,1,0,0,0,-1,-1,-1};
        int c2Dir[]={1,-1,0,1,-1,0,1,-1,0};
        for(int i=0;i<9;i++){
            int newC1=c1+c1Dir[i];
            int newC2=c2+c2Dir[i];
            nextSol=max(nextSol,solveRecMem(r+1,newC1,newC2,grid,dp));
        }

        return dp[r][c1][c2]=nextSol==INT_MIN ? INT_MIN : ans+nextSol;
    }


    int cherryPickup(vector<vector<int>>& grid) {
        // Recursion
        // int n=grid.size();
        // int m=grid[0].size();
        // int ans=solveRec(0,0,m-1,grid);
        // return ans==INT_MIN ? 0 : ans;


        // Recursion + Memoization 
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<vector<int>>> dp(n,vector<vector<int>>(m,vector<int>(m,-1)));
        int ans=solveRecMem(0,0,m-1,grid,dp);
        return ans==INT_MIN ? 0 : ans;
    }
};
// ************************************ My Solution [DP] - Two travellers approach ************************************