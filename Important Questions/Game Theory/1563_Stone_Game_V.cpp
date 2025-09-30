// *********************************************** My Solution ***********************************************
class Solution {
    public:
    int solveRec(int l,int r,vector<int>& stoneValue,vector<int> &prefixSum){
        if(l==r) return 0;

        int maxScore=0;
        // i<r as partition can't be empty
        for(int i=l;i<r;i++){
            int left=prefixSum[i+1]-prefixSum[l];
            int right=prefixSum[r+1]-prefixSum[i+1];
            
            // Bob always gives minimum score to alice
            if(left<right){
                maxScore=max(maxScore,left+solveRec(l,i,stoneValue,prefixSum));
            }else if(left>right){
                maxScore=max(maxScore,right+solveRec(i+1,r,stoneValue,prefixSum));
            }else{
                maxScore=max({maxScore,right+solveRec(i+1,r,stoneValue,prefixSum),left+solveRec(l,i,stoneValue,prefixSum)});
            }

        } 
        return maxScore;
    }


    int solveRec_Mem(int l,int r,vector<int>& stoneValue,vector<int> &prefixSum,vector<vector<int>> &dp){
        if(l==r) return 0;

        if(dp[l][r]!=-1) return dp[l][r];

        int maxScore=0;
        // i<r as partition can't be empty
        for(int i=l;i<r;i++){
            int left=prefixSum[i+1]-prefixSum[l];
            int right=prefixSum[r+1]-prefixSum[i+1];
            
            // Bob always gives minimum score to alice
            if(left<right){
                maxScore=max(maxScore,left+solveRec_Mem(l,i,stoneValue,prefixSum,dp));
            }else if(left>right){
                maxScore=max(maxScore,right+solveRec_Mem(i+1,r,stoneValue,prefixSum,dp));
            }else{
                maxScore=max({maxScore,right+solveRec_Mem(i+1,r,stoneValue,prefixSum,dp),left+solveRec_Mem(l,i,stoneValue,prefixSum,dp)});
            }

        } 
        return dp[l][r]=maxScore;

    }

    int stoneGameV(vector<int>& stoneValue) {
        // Recursion 
        // int n=stoneValue.size();
        // vector<int> prefixSum(n+1,0);
        // for(int i=0;i<n;i++) prefixSum[i+1]=prefixSum[i]+stoneValue[i];
        // return solveRec(0,n-1,stoneValue,prefixSum);


        // Recursion + Memoization
        int n=stoneValue.size();
        vector<int> prefixSum(n+1,0);
        for(int i=0;i<n;i++) prefixSum[i+1]=prefixSum[i]+stoneValue[i];
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        return solveRec_Mem(0,n-1,stoneValue,prefixSum,dp);
    }
};
// *********************************************** My Solution ***********************************************