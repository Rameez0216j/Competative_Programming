// ******************************************* My Solution [DP] *******************************************
class Solution {
    public:
    int solveRec(int left,int right,int count,vector<int>& boxes){
        if(left>right) return 0;

        // Case1
        int ind=left;
        while(ind<=right && boxes[ind]==boxes[left]) ind++;
        count+=(ind-left);
        int case1=count*count+solveRec(ind,right,0,boxes);

        // case 2 : slip curr sequence and search for merging
        int case2=0;
        for(int i=ind;i<=right;i++){
            if(boxes[i]==boxes[left]){
                int temp=solveRec(ind,i-1,0,boxes)+solveRec(i,right,count,boxes);
                case2=max(case2,temp);
            }
        }

        return max(case1,case2);
    }


    int solveRecMem(int left, int right, int count, vector<int>& boxes, vector<vector<vector<int>>> &dp) {
        if (left > right) return 0;

        int origCount = count; // This is important (you always put DP on state when you arrive to Memoized function not modified ones)
        if (dp[left][right][origCount] != -1)
            return dp[left][right][origCount];

        int color = boxes[left];
        int ind = left;
        while (ind <= right && boxes[ind] == color) ind++;
        count += (ind - left);

        // Case 1: Remove the grouped boxes directly
        int case1 = count * count + solveRecMem(ind, right, 0, boxes, dp);

        // Case 2: Try merging with future same-colored boxes
        int case2 = 0;
        for (int i = ind; i <= right; i++) {
            if (boxes[i] == color) {
                int temp = solveRecMem(ind, i - 1, 0, boxes, dp) + solveRecMem(i, right, count, boxes, dp);
                case2 = max(case2, temp);
            }
        }

        return dp[left][right][origCount] = max(case1, case2);
    }


    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));887_Super_Egg_Drop.cpp
        return solveRecMem(0, n - 1, 0, boxes, dp);
    }

};
// ******************************************* My Solution [DP] *******************************************