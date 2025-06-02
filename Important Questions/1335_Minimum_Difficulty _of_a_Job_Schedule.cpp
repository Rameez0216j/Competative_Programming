
// Solution : https://www.youtube.com/watch?v=smTnSl6UKi0&list=PLpIkg8OmuX-L_QqcKB5abYynQbonaNcq3&index=1&t=1467s
// *************************************** My solution - [DP] ***************************************
class Solution {
    public:
    int solveRec(int ind,int d, vector<int>& jobDifficulty){
        int n=jobDifficulty.size();
        if(ind>=n) return INT_MAX;
        if(d==1){
            int maxi=0;
            for(int i=ind;i<n;i++) maxi=max(maxi,jobDifficulty[i]);
            return maxi;
        }

        int maxi=0;
        int nextSol=INT_MAX;
        int ans=INT_MAX;
        // n-d+1 as we need to do one job atleast per day ==> +1 as we are doing one job right now
        for(int i=ind;i<(n-d+1);i++){
            maxi=max(maxi,jobDifficulty[i]);
            nextSol=maxi + min(nextSol,solveRec(i+1,d-1,jobDifficulty));
            ans=min(ans,nextSol);
        }
        return ans;;
    }


    int solveRecMem(int ind,int d, vector<int>& jobDifficulty,vector<vector<int>> &dp){
        int n=jobDifficulty.size();
        if(ind>=n) return INT_MAX;
        if(d==1){
            int maxi=0;
            for(int i=ind;i<n;i++) maxi=max(maxi,jobDifficulty[i]);
            return maxi;
        }

        if(dp[ind][d]!=-1) return dp[ind][d];

        int maxi=0;
        int nextSol=INT_MAX;
        int ans=INT_MAX;
        // n-d+1 as we need to do one job atleast per day ==> +1 as we are doing one job right now
        for(int i=ind;i<(n-d+1);i++){
            maxi=max(maxi,jobDifficulty[i]);
            nextSol=maxi + min(nextSol,solveRecMem(i+1,d-1,jobDifficulty,dp));
            ans=min(ans,nextSol);
        }

        return dp[ind][d]=ans;;
    }

    int minDifficulty(vector<int>& jobDifficulty, int d) {
        // Recursion
        // int n=jobDifficulty.size();
        // if(d>n) return -1;
        // return solveRec(0,d,jobDifficulty);


        // Recursion + Memoization
        int n=jobDifficulty.size();
        if(d>n) return -1;
        vector<vector<int>> dp(n+1,vector<int>(d+1,-1));
        return solveRecMem(0,d,jobDifficulty,dp);
    }
};
// *************************************** My solution - [DP] ***************************************