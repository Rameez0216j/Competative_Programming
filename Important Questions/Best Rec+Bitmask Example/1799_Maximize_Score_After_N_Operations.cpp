// Solution : https://www.youtube.com/watch?v=CTYIzzT9agE
// ************************** My Solution [Recursion ==> TLE] **************************
/*
class Solution {
    public:
    int solveRec(int opCount,vector<bool> &isAvailable,vector<int>& nums){
        int n=nums.size();
        int ans=0;
        for(int i=0;i<n;i++){
            if(!isAvailable[i]) continue;
            for(int j=i+1;j<n;j++){
                if(!isAvailable[j]) continue;

                isAvailable[i]=false;
                isAvailable[j]=false;

                int solveNext=solveRec(opCount+1,isAvailable,nums);
                ans=max(ans,opCount*__gcd(nums[i],nums[j]) + solveNext);

                isAvailable[i]=true;
                isAvailable[j]=true;
            }
        }

        return ans;
    }


    int maxScore(vector<int>& nums) {
        int n=nums.size();
        vector<bool> isAvailable(n,true);
        return solveRec(1,isAvailable,nums);
    }
};
*/
// ************************** My Solution [Recursion ==> TLE] **************************





// ************************** My Solution [Recursion + Memoization] **************************
class Solution {
    public:
    int solveRec(int opCount,int isTaken,vector<int>& nums){
        if(opCount > (nums.size()/2)) return 0;

        int n=nums.size();
        int ans=0;
        for(int i=0;i<n;i++){
            if(isTaken & (1<<i)) continue;
            for(int j=i+1;j<n;j++){
                if(isTaken & (1<<j)) continue;

                int newMask = isTaken | (1 << i) | (1 << j);
                int solveNext = solveRec(opCount + 1, newMask, nums);
                ans = max(ans, opCount * __gcd(nums[i], nums[j]) + solveNext);
            }
        }

        return ans;
    }

    int solveRec_Mem(int opCount,int isTaken,vector<int>& nums,vector<vector<int>> &dp){
        if(opCount > (nums.size()/2)) return 0;
        
        if(dp[opCount][isTaken]!=-1) return dp[opCount][isTaken];

        int n=nums.size();
        int ans=0;
        for(int i=0;i<n;i++){
            if(isTaken & (1<<i)) continue;
            for(int j=i+1;j<n;j++){
                if(isTaken & (1<<j)) continue;

                int newMask = isTaken | (1 << i) | (1 << j);
                int solveNext = solveRec_Mem(opCount + 1, newMask, nums,dp);
                ans = max(ans, opCount * __gcd(nums[i], nums[j]) + solveNext);
            }
        }

        return dp[opCount][isTaken]=ans;
    }


    int maxScore(vector<int>& nums) {
        // Recursion
        // int n=nums.size();
        // int isAvailable=0;
        // return solveRec(1,isAvailable,nums);


        // Recursion + Memoization
        int isAvailable=0;
        int n = nums.size();
        int totalStates = 1 << n; // 2^n
        int maxOps = n / 2 + 1;

        vector<vector<int>> dp(maxOps, vector<int>(1 << n, -1));
        return solveRec_Mem(1,isAvailable,nums,dp);
    }
};
// ************************** My Solution [Recursion + Memoization] **************************