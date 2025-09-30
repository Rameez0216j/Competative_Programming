class Solution {
    public:
    /*
        string str1B=s1.substr(i+1,n); ==> this will also work
    */
    bool solveRec(string s1, string s2){
        int n=s1.size();

        // Pruning
        string t1 = s1, t2 = s2;
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) return false;

        if(s1==s2) return true;

        for(int i=1;i<n;i++){
            string str1A=s1.substr(0,i);
            string str1B=s1.substr(i,n-i);
            string str2A=s2.substr(0,i);
            string str2B=s2.substr(i,n-i);
            string str2C=s2.substr(0,n-i);
            string str2D=s2.substr(n-i,i);


            bool not_swapped=solveRec(str1A,str2A) && solveRec(str1B,str2B);
            bool swapped=solveRec(str1A,str2D) && solveRec(str1B,str2C);

            if(not_swapped || swapped) return true;
        }
        return false;
    }



    bool solveRec_Mem(string s1, string s2,unordered_map<string,bool> &dp){
        int n=s1.size();
        string dp_string=s1+'#'+s2;
        if(dp.count(dp_string)) return dp[dp_string];

        // Pruning
        string t1 = s1, t2 = s2;
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        if (t1 != t2) return dp[dp_string]=false;

        if(s1==s2) return dp[dp_string]=true;


        for(int i=1;i<n;i++){
            string str1A=s1.substr(0,i);
            string str1B=s1.substr(i,n-i);
            string str2A=s2.substr(0,i);
            string str2B=s2.substr(i,n-i);
            string str2C=s2.substr(0,n-i);
            string str2D=s2.substr(n-i,i);

            bool not_swapped=solveRec_Mem(str1A,str2A,dp) && solveRec_Mem(str1B,str2B,dp);
            bool swapped=solveRec_Mem(str1A,str2D,dp) && solveRec_Mem(str1B,str2C,dp);

            if(not_swapped || swapped) return dp[dp_string]=true;
        }
        return dp[dp_string]=false;
    }

    bool isScramble(string s1, string s2) {
        // Recursion
        // return solveRec(s1,s2);


        // Recursion + Memoization
        unordered_map<string,bool> dp;
        return solveRec_Mem(s1,s2,dp);
    }
};