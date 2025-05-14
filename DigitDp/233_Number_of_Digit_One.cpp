class Solution {
    public:
    // count variable is actually counting the number of ones appeared in the combination
    int solve(int ind,string num,int count,bool tight){
        if(ind==num.size()) return count;

        int ans=0;
        int last= (tight==true) ? num[ind]-'0' : 9;
        for(int i=0;i<=last;i++){
            ans+= solve(ind + 1, num,count+(i==1), tight && (i == last));
        }
        return ans;
    }

    int solveMem(int ind,string num,int count,bool tight,vector<vector<vector<int>>> &dp){
        if(ind==num.size()) return count;

        if(dp[ind][count][tight]!=-1) return dp[ind][count][tight];

        int ans=0;
        int last= (tight==true) ? num[ind]-'0' : 9;
        for(int i=0;i<=last;i++){
            ans+= solveMem(ind + 1, num,count+(i==1), tight && (i == last),dp);
        }
        return dp[ind][count][tight]=ans;
    }
    
    int countDigitOne(int n) {
        // Recursion
        // string num=to_string(n);
        // return solve(0,num,0,true);

        // Recursion + Memoization
        string num=to_string(n);
        vector<vector<vector<int>>> dp(num.size()+1,vector<vector<int>>(num.size()+1,vector<int>(2,-1)));
        return solveMem(0,num,0,true,dp);
    }
};