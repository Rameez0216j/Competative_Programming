// ********************************************** My Solution **********************************************
/*
class Solution {
    public:
    int solveRec(int curr,vector<int>& stoneValue){
        int n=stoneValue.size();
        if(curr>=n) return 0;

        int res=INT_MIN;
        int sum=0;
        for(int i=0;i<3;i++){
            if(curr+i<n){
                sum+=stoneValue[curr+i];
                res=max(res,sum-solveRec(curr+i+1,stoneValue));
            }
        }
        return res;
    }



    int solveRec_Mem(int curr,vector<int>& stoneValue,vector<int> &dp){
        int n=stoneValue.size();
        if(curr>=n) return 0;

        if(dp[curr]!=INT_MIN) return dp[curr];

        int res=INT_MIN;
        int sum=0;
        for(int i=0;i<3;i++){
            if(curr+i<n){
                sum+=stoneValue[curr+i];
                res=max(res,sum-solveRec_Mem(curr+i+1,stoneValue,dp));
            }
        }
        return dp[curr]=res;
    }


    string stoneGameIII(vector<int>& stoneValue) {
        // Recursion
        // int diff=solveRec(0,stoneValue);
        // if(diff<0) return "Bob";
        // else if(diff>0) return "Alice";
        // return "Tie";


        // Recursion + Memoization
        int n=stoneValue.size();
        vector<int> dp(n+1,INT_MIN);
        int diff=solveRec_Mem(0,stoneValue,dp);
        if(diff<0) return "Bob";
        else if(diff>0) return "Alice";
        return "Tie";
    }
};
*/
// ********************************************** My Solution **********************************************






// ******************************************* My Solution [cleaned] *******************************************
class Solution {
public:
    int dfs(int index, vector<int>& stoneValue, vector<int>& dp) {
        int n = stoneValue.size();
        if (index >= n) return 0;

        if (dp[index] != INT_MIN) return dp[index];

        int maxDiff = INT_MIN;
        int sum = 0;

        // Try picking 1, 2 or 3 stones
        for (int i = 0; i < 3 && index + i < n; ++i) {
            sum += stoneValue[index + i];
            int opponentScore = dfs(index + i + 1, stoneValue, dp);
            maxDiff = max(maxDiff, sum - opponentScore); // Best Alice can do
        }

        return dp[index] = maxDiff;
    }

    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n, INT_MIN);

        int diff = dfs(0, stoneValue, dp); // Alice's score difference over Bob

        if (diff > 0) return "Alice";
        else if (diff < 0) return "Bob";
        else return "Tie";
    }
};
// ******************************************* My Solution [cleaned] *******************************************