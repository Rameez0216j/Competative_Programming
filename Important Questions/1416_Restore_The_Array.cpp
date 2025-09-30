// *************************************** My Solution ***************************************
class Solution {
    int mod=1e9+7;

    public:
    int solveRec(int idx,string &s, int k){
        if(idx>=s.size()) return 1;
        if(s[idx]=='0') return 0; // leading zeros
        
        int ans=0;
        int val=0;
        for(int i=idx;i<s.size();i++){
            int digit=s[i]-'0';
            val=val*10+digit;
            if(val<=k) ans+=solveRec(i+1,s,k);
            else break;
        }

        return ans;
    }



    /*
    int solveRec_Mem(int idx,string &s, int k,vector<int> &dp){
        if(idx>=s.size()) return 1;
        if(s[idx]=='0') return 0; // leading zeros

        if(dp[idx]!=-1) return dp[idx];
        
        int ans=0;
        int val=0;
        for(int i=idx;i<s.size();i++){
            int digit=s[i]-'0';
            val=val*10+digit;
            if(val<=k) ans+=solveRec_Mem(i+1,s,k,dp);
            else break;
        }

        return dp[idx]=ans;
    }
    */

    // With modulo
    const int MOD = 1e9 + 7;
    int solveRec_Mem(int idx, string &s, int k, vector<int> &dp) {
        if (idx == s.size()) return 1;
        if (s[idx] == '0') return 0;
        if (dp[idx] != -1) return dp[idx];

        long long num = 0;
        int ways = 0;

        for (int i = idx; i < s.size(); ++i) {
            num = num * 10 + (s[i] - '0');
            if (num > k) break;
            ways = (ways + solveRec_Mem(i + 1, s, k, dp)) % MOD;
        }

        return dp[idx] = ways;
    }



    int numberOfArrays(string s, int k) {
        // Recursion
        // return solveRec(0,s,k);


        // Recursion + Memoization
        int n=s.size();
        vector<int> dp(n+1,-1);
        return solveRec_Mem(0,s,k,dp);
    }
};
// *************************************** My Solution ***************************************

