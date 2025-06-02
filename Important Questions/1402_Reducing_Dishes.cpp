// Solution : https://www.youtube.com/watch?v=JIdXXP9VjDE&t=1094s
// **************************************** My solution ****************************************
class Solution {
    public:
    int solveRec(int ind,int time,vector<int>& satisfaction){
        if(ind>=satisfaction.size()) return 0;

        int include=satisfaction[ind]*time+solveRec(ind+1,time+1,satisfaction);
        int exclude=solveRec(ind+1,time,satisfaction);
        return max(include,exclude);
    }

    int solveRecMem(int ind,int time,vector<int>& satisfaction,vector<vector<int>> &dp){
        if(ind>=satisfaction.size()) return 0;

        if(dp[ind][time]!=-1) return dp[ind][time];

        int include=satisfaction[ind]*time+solveRecMem(ind+1,time+1,satisfaction,dp);
        int exclude=solveRecMem(ind+1,time,satisfaction,dp);
        return dp[ind][time]=max(include,exclude);
    }

    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(),satisfaction.end());

        // Recursion
        // return solveRec(0,1,satisfaction);

        // Recursion + Memoization
        int n=satisfaction.size();
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        return solveRecMem(0,1,satisfaction,dp);
    }
};
// **************************************** My solution ****************************************







// **************************************** Solution ****************************************
/*
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        // Step 1: Sort the satisfaction values in descending order.
        // This allows us to consider high-satisfaction dishes first,
        // and check if including more dishes increases the overall like-time.
        sort(satisfaction.begin(), satisfaction.end(), greater<int>());

        int presum = 0; // Keeps track of the running sum of included satisfaction values.
        int res = 0;    // Stores the final result: maximum like-time coefficient.

        // Step 2: Iterate through the sorted satisfaction list
        for (int i = 0; i < satisfaction.size(); i++) {
            // Add current dish's satisfaction to the prefix sum
            presum += satisfaction[i];

            // If adding this dish makes the prefix sum negative,
            // it means including this dish would reduce the total result.
            // So we stop including further dishes.
            if (presum < 0) {
                break;
            }

            // Add current prefix sum to result.
            // This is equivalent to increasing the like-time coefficient optimally.
            res += presum;
        }

        // Step 3: Return the maximum like-time coefficient obtained
        return res;
    }
};
*/
// **************************************** Solution ****************************************