// Solution : https://www.youtube.com/watch?v=Zyzs3AuqPRw&t=1615s
// ******************************************** My Solution ********************************************
class Solution {
    int ans=0;
    public:
    // Memoization of this will give MLE
    void solveRec(int ind,int left,int right,vector<int>& rods){
        if(ind>=rods.size()){
            if(left==right) ans=max(ans,left);
            return;
        }

        solveRec(ind+1,left,right,rods);
        solveRec(ind+1,left+rods[ind],right,rods);
        solveRec(ind+1,left,right+rods[ind],rods);
    }
    
    // Instaed of using left and right we can use difference between them 
    int solveRec2(int ind,int diff,vector<int>& rods){
        if(ind>=rods.size()){
            if(diff==0) return 0;
            return INT_MIN;
        }

        int skip=solveRec2(ind+1,diff,rods);
        int add_left=rods[ind]+solveRec2(ind+1,diff+rods[ind],rods); // diff = left - right, so [(left+x) - right] ==> diff+x
        int add_right=rods[ind]+solveRec2(ind+1,diff-rods[ind],rods); // diff = left - right, so [left- (right+x)] ==> diff-x

        return max({skip,add_left,add_right});
    }


    int solveRec2_Mem(int ind,int diff,vector<int>& rods,vector<vector<int>> &dp){
        if(ind>=rods.size()){
            if(diff==0) return 0;
            return INT_MIN;
        }

        if(dp[ind][diff+5001]!=-1) return dp[ind][diff+5001];

        int skip=solveRec2_Mem(ind+1,diff,rods,dp);
        int add_left=rods[ind]+solveRec2_Mem(ind+1,diff+rods[ind],rods,dp); // diff = left - right, so [(left+x) - right] ==> diff+x
        int add_right=rods[ind]+solveRec2_Mem(ind+1,diff-rods[ind],rods,dp); // diff = left - right, so [left- (right+x)] ==> diff-x

        return dp[ind][diff+5001]=max({skip,add_left,add_right});
    }


    int tallestBillboard(vector<int>& rods) {
        // Recurson 1
        // solveRec(0,0,0,rods);
        // return ans;


        // Recursion 2
        // return solveRec2(0,0,rods)/2;


        // Recursion 2 + Memoization
        int n=rods.size();
        vector<vector<int>> dp(n+1,vector<int>(10001,-1)); // 5000+5000+1 
        return solveRec2_Mem(0,0,rods,dp)/2;
    }
};
// ******************************************** My Solution ********************************************