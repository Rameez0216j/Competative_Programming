// **************************************** My Solution ****************************************
class Solution {
    public:
    int solveRec(int ind,int curr,string &ring,string &key,unordered_map<int,vector<int>> &positions){
        int n=ring.size();
        if(ind>=key.size()) return 0;

        int ans=INT_MAX;
        for(int pos: positions[key[ind]]){
            // 1+ for pressing and min(abs(curr-pos),n-abs(curr-pos)) ==> for rotating the dial both in anti-clockwise and clolckwise
            int temp=1+min(abs(curr-pos),n-abs(curr-pos)) + solveRec(ind+1,pos,ring,key,positions);
            ans=min(ans,temp);
        }
        return ans;
    }


    int solveRec_Mem(int ind,int curr,string &ring,string &key,unordered_map<int,vector<int>> &positions,vector<vector<int>> &dp){
        int n=ring.size();
        if(ind>=key.size()) return 0;

        if(dp[ind][curr]!=-1) return dp[ind][curr];

        int ans=INT_MAX;
        for(int pos: positions[key[ind]]){
            // 1+ for pressing and min(abs(curr-pos),n-abs(curr-pos)) ==> for rotating the dial both in anti-clockwise and clolckwise
            int temp=1+min(abs(curr-pos),n-abs(curr-pos)) + solveRec_Mem(ind+1,pos,ring,key,positions,dp);
            ans=min(ans,temp);
        }
        return dp[ind][curr]=ans;
    }

    int findRotateSteps(string ring, string key) {
        // Recursion
        // unordered_map<int,vector<int>> positions;
        // for(int i=0;i<ring.size();i++) positions[ring[i]].push_back(i);
        // return solveRec(0,0,ring,key,positions);


        // Recursion + Memoization
        int n=key.size();
        int m=ring.size();
        unordered_map<int,vector<int>> positions;
        for(int i=0;i<ring.size();i++) positions[ring[i]].push_back(i);

        vector<vector<int>> dp(n+1,vector<int>(m+1,-1));
        return solveRec_Mem(0,0,ring,key,positions,dp);
    }
};
// **************************************** My Solution ****************************************