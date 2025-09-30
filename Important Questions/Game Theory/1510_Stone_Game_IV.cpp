// *************************************** My Solution ***************************************
class Solution {
    public:
    int canWin(int n){
        if(n==1) return true;

        bool ans=false;
        for(int i=1;i*i<=n;i++){
            // returning true for !canWin(n-i*i) because it is oppoent turn
            if(!canWin(n-i*i)) return true;
        }
        return false;
    }


    int canWin_Mem(int n,vector<int> &dp){
        if(n==1) return true;

        if(dp[n]!=-1) return dp[n];

        bool ans=false;
        for(int i=1;i*i<=n;i++){
            // returning true for !canWin(n-i*i) because it is oppoent turn
            if(!canWin_Mem(n-i*i,dp)) return dp[n]=true;
        }
        return dp[n]=false;
    }

    bool winnerSquareGame(int n) {
        // canWin is a function determining that if alice acan win
        
        // Recursion
        // return canWin(n);


        // Recursion + Memoization
        vector<int> dp(n+1,-1);
        return canWin_Mem(n,dp);
    }
};
// *************************************** My Solution ***************************************