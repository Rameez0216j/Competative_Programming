class Solution {
    public:
    int solveRec(int eggsCount,int buildingHeight){
        if(buildingHeight==1 || buildingHeight==0) return buildingHeight;
        if(eggsCount==1) return buildingHeight; // we need to try all the floors from ground floor and maybe the f is top floor so returned buildingHeight
        
        int ans=INT_MAX;
        // Searching all floors
        for(int floor=1;floor<=buildingHeight;floor++){
            // temp=max(break,notBreak)
            int temp=1+max(solveRec(eggsCount-1,floor-1),solveRec(eggsCount,buildingHeight-floor)); // +1 as one try is already used
            ans=min(ans,temp);
        }

        return ans;
    }


    int solveRecMem(int eggsCount,int buildingHeight,vector<vector<int>> &dp){
        if(buildingHeight==1 || buildingHeight==0) return buildingHeight;
        if(eggsCount==1) return buildingHeight; // we need to try all the floors from ground floor and maybe the f is top floor so returned buildingHeight

        if(dp[eggsCount][buildingHeight]!=-1) return dp[eggsCount][buildingHeight];
        
        int ans=INT_MAX;
        // Searching all floors
        for(int floor=1;floor<=buildingHeight;floor++){
            // temp=max(break,notBreak)
            int temp=1+max(solveRecMem(eggsCount-1,floor-1,dp),solveRecMem(eggsCount,buildingHeight-floor,dp)); // +1 as one try is already used
            ans=min(ans,temp);
        }

        return dp[eggsCount][buildingHeight]=ans;
    }

    int solveRecMem2(int eggsCount, int buildingHeight, vector<vector<int>> &dp) {
        // Base cases:
        if (buildingHeight == 0 || buildingHeight == 1) return buildingHeight;

        // If only one egg is left, we have to do linear search (worst case)
        if (eggsCount == 1) return buildingHeight;

        // If already computed, return from dp
        if (dp[eggsCount][buildingHeight] != -1) return dp[eggsCount][buildingHeight];

        int ans = INT_MAX;
        int start = 1, end = buildingHeight;

        // Using Binary Search to minimize the worst-case number of drops
        while (start <= end) {
            int floor = start + (end - start) / 2;

            // Two possibilities:
            // 1. Egg breaks -> check below floors with one less egg
            int lowerPart = solveRecMem2(eggsCount - 1, floor - 1, dp);
            // 2. Egg doesn't break -> check above floors with same number of eggs
            int upperPart = solveRecMem2(eggsCount, buildingHeight - floor, dp);

            // Calculate the worst case if we drop from 'floor'
            int temp = 1 + max(lowerPart, upperPart);

            // We want to minimize the worst-case number of attempts
            ans = min(ans, temp);

            // 🔥 Key logic:
            // As for temp, we are selecting max(lowerPart, upperPart),
            // so we move towards the max value side and completely ignore the lesser side.
            //
            // Why?
            // Because in the worst-case scenario, the larger part will dominate.
            // To minimize the max, we must reduce the larger side.

            if (upperPart < lowerPart) {
                // lowerPart (egg breaks) is worse, move left to reduce it
                end = floor - 1;
            } else {
                // upperPart (egg survives) is worse, move right to reduce it
                start = floor + 1;
            }
        }

        return dp[eggsCount][buildingHeight] = ans;
    }


    int superEggDrop(int eggsCount,int buildingHeight) {
        // Recursion
        // return solveRec(eggsCount,buildingHeight);


        // Recursion + Memoization
        // vector<vector<int>> dp(eggsCount+1,vector<int>(buildingHeight+1,-1));
        // return solveRecMem(eggsCount,buildingHeight,dp);


        // Recursion + Memoization + Binary search
        vector<vector<int>> dp(eggsCount+1,vector<int>(buildingHeight+1,-1));
        return solveRecMem2(eggsCount,buildingHeight,dp);
    }
};