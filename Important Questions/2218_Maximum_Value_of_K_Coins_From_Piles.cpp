// Solution : https://www.youtube.com/watch?v=sH276uTmZ80&t=273s
// ********************************************* My Solution *********************************************
class Solution {
    public:
    int solveRec(int ind,vector<vector<int>>& piles, int k){
        if(k==0) return 0;
        if(ind==piles.size()) return 0;

        int ans=0;
        int n=piles.size();
        int collected=0;
        for(int j=0;j<=piles[ind].size() && j<=k;j++){
            // For j==0 we are skipping current pile
            if(j-1 >=0) collected+=piles[ind][j-1];
            ans=max(ans,collected+solveRec(ind+1,piles,k-j)); // k-j+1  ==> because j is 0 based index
        }
        return ans;
    }


    int solveRec_Mem(int ind,vector<vector<int>>& piles, int k,vector<vector<int>> &dp){
        if(k==0) return 0;
        if(ind==piles.size()) return 0;

        if(dp[ind][k]!=-1) return dp[ind][k];

        int ans=0;
        int n=piles.size();
        int collected=0;
        for(int j=0;j<=piles[ind].size() && j<=k;j++){
            // For j==0 we are skipping current pile
            if(j-1 >=0) collected+=piles[ind][j-1];
            ans=max(ans,collected+solveRec_Mem(ind+1,piles,k-j,dp)); // k-j+1  ==> because j is 0 based index
        }
        return dp[ind][k]=ans;
    }

    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        // Recursion
        // return solveRec(0,piles,k);


        // Recursion + Memoization
        int n=piles.size();
        vector<vector<int>> dp(n+1,vector<int>(k+1,-1));
        return solveRec_Mem(0,piles,k,dp);
    }
};
// ********************************************* My Solution *********************************************