// ************************************* My Solution (TLE) *************************************
class Solution {
    int M=1e9+7;
    public:

    // Recursive function to count the number of ways to distribute 'k' items into 'n' bins
    int solveRec(int n, int k) {
        // Base case 1: If there are no items to distribute, there's exactly one way (do nothing)
        if (k == 0) return 1;

        // Base case 2: If there are no bins but some items to distribute, no way to do so
        if (n == 0) return 0;

        int ans = 0;

        // Try distributing 0 to min(n-1, k) items in the current bin
        // This ensures that no bin gets more than (n-1) items which prevents over-counting in some formulations
        for (int i = 0; i <= min(n - 1, k); i++) {
            // Recursively solve for remaining (n-1) bins and (k-i) items
            ans += solveRec(n - 1, k - i);
        }

        return ans;
    }



    // Without comments
    // int solveRec(int n,int k){
    //     if(k==0) return 1;
    //     if(n==0) return 0;

    //     int ans=0;
    //     for(int i=0;i<=min(n-1,k);i++) ans+=solveRec(n-1,k-i);
    //     return ans;
    // }

    // O(n*k*k) ==> k from for loop inside ==> 10^9 ==> TLE
    int solveRec_Mem(int n,int k,vector<vector<int>> &dp){
        if(k==0) return 1;
        if(n==0) return 0;

        if(dp[n][k]!=-1) return dp[n][k];

        int ans=0;
        for(int i=0;i<=min(n-1,k);i++) ans=( ans%M + solveRec_Mem(n-1,k-i,dp)%M )%M;

        return dp[n][k]=ans;
    }


    // Tabulation code with comments
    // int solveTab(int numElements, int numInversePairs) {
    //     // Create a DP table with dimensions (numElements + 1) x (numInversePairs + 1)
    //     vector<vector<int>> dp(numElements + 1, vector<int>(numInversePairs + 1, 0));

    //     // Base case: There's 1 way to form an array with any number of elements and 0 inverse pairs (sorted array)
    //     for (int i = 0; i <= numElements; i++) dp[i][0] = 1;

    //     // Base case: No way to form an array with 0 elements and any number of inverse pairs
    //     // This is already initialized to 0, so we don't need to explicitly set it

    //     // Filling the DP table using bottom-up approach (Tabulation)
    //     for (int num = 1; num <= numElements; num++) {  // num refers to number of elements considered so far
    //         for (int inv = 1; inv <= numInversePairs; inv++) {  // inv refers to the current number of inverse pairs
    //             int totalWays = 0;

    //             // Summing the number of ways to form inv inverse pairs with num elements
    //             // The sum is from previous rows (i.e., dp[num-1][inv-p])
    //             for (int p = 0; p <= min(num - 1, inv); p++) { // p refers to how many elements are placed in positions contributing to inverse pairs
    //                 totalWays = (totalWays + dp[num - 1][inv - p]) % M;
    //             }

    //             // Store the result in the DP table for the current num elements and inv inverse pairs
    //             dp[num][inv] = totalWays;
    //         }
    //     }

    //     // The final answer is stored in dp[numElements][numInversePairs]
    //     return dp[numElements][numInversePairs];
    // }


    // Tabulation code with cleaned comments
    int solveTab(int n,int k){
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));

        for(int i=0;i<=n;i++) dp[i][0]=1;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                int ans=0;
                for(int p=0;p<=min(i-1,j);p++) ans=( ans%M + dp[i-1][j-p]%M )%M;
                dp[i][j]=ans;
            }
        }

        return dp[n][k];
    }




    // Prefix sum Optimization
    /*
        --- Derivation of Optimized Recurrence ---

        Original recurrence:
            dp[n][k] = sum_{x = 0 to min(n - 1, k)} dp[n - 1][k - x]
            // We place the nth number in all possible positions (0 to n-1),
            // each position x contributes x inverse pairs.

        So we are summing:
            dp[n][k] = dp[n - 1][k] 
                    + dp[n - 1][k - 1] 
                    + dp[n - 1][k - 2] 
                    + ... 
                    + dp[n - 1][k - (n - 1)]

        Let’s say we already have:
            dp[n][k - 1] = dp[n - 1][k - 1] + dp[n - 1][k - 2] + ... + dp[n - 1][k - n]

        Then:
            dp[n][k] = dp[n][k - 1] + dp[n - 1][k]

            BUT:
            If k ≥ n, then dp[n][k - 1] already includes dp[n - 1][k - n],
            which shouldn't be included in dp[n][k] (because x must be ≤ n - 1)

            So we subtract that extra term:
            dp[n][k] = dp[n][k - 1] + dp[n - 1][k] - dp[n - 1][k - n]

        Final optimized recurrence:
            dp[n][k] = dp[n][k - 1] + dp[n - 1][k] - dp[n - 1][k - n]   (if k ≥ n)
    */
    int solveTabPrefSum(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        dp[0][0] = 1; // Base case

        for (int num = 1; num <= n; num++) {
            dp[num][0] = 1; // Only 1 way to have 0 inverse pairs: sorted array

            for (int inv = 1; inv <= k; inv++) {
                int val = (dp[num][inv - 1] + dp[num - 1][inv]) % M;
                if (inv >= num) val = (val - dp[num - 1][inv - num] + M) % M;
                dp[num][inv] = val;
            }
        }

        return dp[n][k];
    }

    int kInversePairs(int n, int k) {
        // Recursion
        // return solveRec(n,k);

        // Recursion + Memoization
        // vector<vector<int>> dp(n+1,vector<int>(k+1,-1));
        // return solveRec_Mem(n,k,dp);

        // Tabulation
        // return solveTab(n,k);

        // Prefix sum OPtimization
        return solveTabPrefSum(n,k);
    }
};
// ************************************* My Solution (TLE) *************************************