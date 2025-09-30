// ************************************** My Solution **************************************
class Solution {
    public:
    bool solveRec(int row,int col,int val,vector<vector<char>>& grid){
        int n=grid.size();
        int m=grid[0].size();

        if(val<0) return false; // This needs to be above last cell checking for base case ==> [[")","("]]
        if(row>=n || col>=m) return false;
        if(row==n-1 && col==m-1){
            val+=(grid[row][col]=='(' ? 1 : -1);
            return val==0;
        }


        return solveRec(row+1,col,val+(grid[row][col]=='(' ? 1 : -1),grid) || solveRec(row,col+1,val+(grid[row][col]=='(' ? 1 : -1),grid);
    }


    bool solveRec_Mem(int row,int col,int val,vector<vector<char>>& grid,vector<vector<vector<int>>> &dp){
        int n=grid.size();
        int m=grid[0].size();

        if(val<0) return false; // This needs to be above last cell checking for base case ==> [[")","("]]
        if(row>=n || col>=m) return false;
        if(row==n-1 && col==m-1){
            val+=(grid[row][col]=='(' ? 1 : -1);
            return val==0;
        }

        if(dp[row][col][val]!=-1) return dp[row][col][val];
        
        return dp[row][col][val]=solveRec_Mem(row+1,col,val+(grid[row][col]=='(' ? 1 : -1),grid,dp) || solveRec_Mem(row,col+1,val+(grid[row][col]=='(' ? 1 : -1),grid,dp);
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        // Recursion
        // return solveRec(0,0,0,grid);


        // Recursion + Memoization
        int n=grid.size();
        int m=grid[0].size();
        int maxVal=m+n+1; // n -> downwards movement , m -> sideways (right) movement + 1(extra)
        vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(m+1,vector<int>(m+n+1,-1)));
        return solveRec_Mem(0,0,0,grid,dp);
    }
};
// ************************************** My Solution **************************************