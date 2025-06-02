// ***************************************** My Solution *****************************************
class Solution {
    public:
    int solveRec(int left,int right,string &str){
        if(left>right) return 0;
        if(left==right) return 1;

        int ind=left;
        while(ind<=right && str[ind]==str[left]) ind++;
        
        // case 1 : print the sequence
        int case1=1+solveRec(ind,right,str);

        // case2
        int case2=INT_MAX;
        for(int i=ind;i<=right;i++){
            if(str[i]==str[left]){
                // merge: str[left] and str[i] printed together
                int temp=solveRec(ind,i-1,str)+solveRec(i,right,str);
                case2=min(case2,temp);
            }
        }

        return min(case1,case2);
    }


    int solveRecMem(int left,int right,string &str,vector<vector<int>> &dp){
        if(left>right) return 0;
        if(left==right) return 1;

        if(dp[left][right]!=-1) return dp[left][right];

        int ind=left;
        while(ind<=right && str[ind]==str[left]) ind++;
        
        // case 1 : print the sequence
        int case1=1+solveRecMem(ind,right,str,dp);

        // case2
        int case2=INT_MAX;
        for(int i=ind;i<=right;i++){
            if(str[i]==str[left]){
                int temp=solveRecMem(ind,i-1,str,dp)+solveRecMem(i,right,str,dp);
                case2=min(case2,temp);
            }
        }

        return dp[left][right]=min(case1,case2);
    }

    int strangePrinter(string s) {
        // Recursion
        // int n=s.size();
        // return solveRec(0,n-1,s);


        // Recursion + Memoization
        int n=s.size();
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        return solveRecMem(0,n-1,s,dp);
    }
};
// ***************************************** My Solution *****************************************



664_Strange_Printer.cpp


// Solution : https://www.youtube.com/watch?v=pV3arpA0TzY
// ***************************************** Solution *****************************************
class Solution {
    public:

    int strangePrinter(string s) {
        // Recursion
        int n=s.size();
        return solveRec(0,n-1,s);
    }
};
// ***************************************** Solution *****************************************