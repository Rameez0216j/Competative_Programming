// *************************************** My Solution ***************************************
class Solution {
    public:
    int getMaxScore(int index, const vector<int>& prefixSum) {
        int n = prefixSum.size();
        if (index == n - 1) return prefixSum[index];

        int chooseCurrent = prefixSum[index] - getMaxScore(index + 1, prefixSum);
        int skipCurrent = getMaxScore(index + 1, prefixSum);

        return max(chooseCurrent, skipCurrent);
    }


    int getMaxScore_Mem(int index, const vector<int>& prefixSum, vector<int> &dp) {
        int n = prefixSum.size();
        if (index == n - 1) return prefixSum[index];

        if(dp[index]!=INT_MIN) return dp[index];

        int chooseCurrent = prefixSum[index] - getMaxScore_Mem(index + 1, prefixSum, dp);
        int skipCurrent = getMaxScore_Mem(index + 1, prefixSum, dp);

        return dp[index]=max(chooseCurrent, skipCurrent);
    }

    int stoneGameVIII(vector<int>& stones) {
        // Recursion
        /*
        int n = stones.size();

        // Calculate prefix sums
        vector<int> prefixSum(n);
        prefixSum[0] = stones[0];
        for (int i = 1; i < n; ++i) prefixSum[i] = prefixSum[i - 1] + stones[i];

        // Start from index 1 as per the constraint: x > 1
        return getMaxScore(1, prefixSum);
        */





        // Recursion + Memoization
        int n = stones.size();
        
        // Calculate prefix sums
        vector<int> prefixSum(n);
        prefixSum[0] = stones[0];
        for (int i = 1; i < n; ++i) prefixSum[i] = prefixSum[i - 1] + stones[i];

        // Start from index 1 as per the constraint: x > 1
        vector<int> dp(n+1,INT_MIN);
        return getMaxScore_Mem(1, prefixSum,dp);
    }
};
// *************************************** My Solution ***************************************

