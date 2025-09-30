// ************************************ My Solution [TLE] ******************************************
/*
class Solution {
    public:
    long long int solveRec(int curr, int m, int n, vector<vector<int>>& prices) {
        if (curr >= prices.size()) return 0;

        int curr_h = prices[curr][0];
        int curr_w = prices[curr][1];
        long long int sell_curr = 0;

        if (curr_h <= m && curr_w <= n) {
            // Cut Horizontally then Vertically
            int cut1_1 = solveRec(curr, m - curr_h, n, prices); 
            int cut1_2 = solveRec(curr, curr_h, n - curr_w, prices);
            
            // Cut Vertically then Horizontally
            int cut2_1 = solveRec(curr, m, n-curr_w, prices); 
            int cut2_2 = solveRec(curr, m - curr_h, curr_w, prices); 

            sell_curr = 1ll*prices[curr][2] + max(cut1_1 + cut1_2, cut2_1 + cut2_2);
        }

        long long int skip_curr = solveRec(curr + 1, m, n, prices);
        return max(sell_curr, skip_curr);
    }

    // TC  ==>  O(curr*m*n*5(calls)) = O(2*10^4*200*200*5) = O(4*10^9)
    long long int solveRec_Mem(int curr, int m, int n, vector<vector<int>>& prices, vector<vector<vector<long long int>>> &dp) {
        if (curr >= prices.size()) return 0;

        if(dp[curr][m][n]!=-1) return dp[curr][m][n];

        int curr_h = prices[curr][0];
        int curr_w = prices[curr][1];
        long long int sell_curr = 0;

        if (curr_h <= m && curr_w <= n) {
            // Cut Horizontally then Vertically
            int cut1_1 = solveRec_Mem(curr, m - curr_h, n, prices, dp); 
            int cut1_2 = solveRec_Mem(curr, curr_h, n - curr_w, prices, dp);
            
            // Cut Vertically then Horizontally
            int cut2_1 = solveRec_Mem(curr, m, n-curr_w, prices, dp); 
            int cut2_2 = solveRec_Mem(curr, m - curr_h, curr_w, prices, dp); 

            sell_curr = 1ll*prices[curr][2] + max(cut1_1 + cut1_2, cut2_1 + cut2_2);
        }

        long long int skip_curr = solveRec_Mem(curr + 1, m, n, prices, dp);
        return dp[curr][m][n]=max(sell_curr, skip_curr);
    }

    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        // Recursion
        // return solveRec(0, m, n, prices);

        // Recursion + Memoization
        int k=prices.size();
        vector<vector<vector<long long int>>> dp(k+1,vector<vector<long long int>>(m+1,vector<long long int>(n+1,-1)));
        return solveRec_Mem(0, m, n, prices,dp);
    }
};
*/
// ************************************ My Solution [TLE] ******************************************
