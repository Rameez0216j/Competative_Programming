// Solution :https://www.youtube.com/watch?v=ECcJUqdumIo&t=573s
/*
    Why Using median :
        📌 Why place the mailbox at the median?

        Let's consider 3 sorted house positions:
            H1        H2        H3

        ✅ Case 1: Place mailbox at H2 (the median)
            H1   ---d1---   H2   ---d2---   H3
                 [ Mailbox Here at H2 ]

            Distances:
            - H1 to M = d1
            - H2 to M = 0
            - H3 to M = d2
            Total = d1 + 0 + d2 = ✅ Minimum

        🚫 Case 2: Place mailbox slightly to the **left** of H2 (by distance x)
            H1   --(d1 - x)--   M   --(d2 + x)--   H2 ----- H3

            - H1 gets x units closer
            - H3 gets x units farther
            - H2 is now x units away

            Total = (d1 - x) + x + (d2 + x) = d1 + d2 + x ❌

        🚫 Case 3: Place mailbox slightly to the **right** of H2 (by distance x)
            H1 ----- H2   --(d1 + x)--   M   --(d2 - x)--   H3

            - H1 gets x units farther
            - H3 gets x units closer
            - H2 is now x units away

            Total = (d1 + x) + x + (d2 - x) = d1 + d2 + x ❌

        🎯 Conclusion:
        - Placing the mailbox at the **median house (H2)** minimizes total distance: d1 + d2
        - Any shift (left or right) adds an **extra distance x** to the total.
        - That’s why we use:
            int median = houses[i + (j - i) / 2];




    NOTE:
        📌 Why do we choose the median as:
            int median = houses[i + (j - i) / 2];

        💡 Key Idea:
            - To minimize the total distance from a mailbox to all houses in a given interval [i..j],
            we must place the mailbox at the **median** of those houses.
            - The median minimizes the sum of absolute differences.

            🔸 Odd number of houses:
            houses = [1, 4, 7]
            Median = 4
            Total cost = |1-4| + |4-4| + |7-4| = 6 ✅ (Minimum)

            🔸 Even number of houses:
            houses = [1, 4, 7, 10]
            True median = (4 + 7) / 2 = 5.5 (not an actual house)

            Cost if mailbox at:
            - 4 (first middle): |1-4| + |4-4| + |7-4| + |10-4| = 12
            - 7 (second middle): |1-7| + |4-7| + |7-7| + |10-7| = 12
            - 5.5 (ideal median): |1-5.5| + |4-5.5| + |7-5.5| + |10-5.5| = 12

            ✨ All yield the same cost — so any middle position works.

            ✅ Since we work with integer positions only (mailbox must be at a house), we choose:
                median = houses[i + (j - i) / 2];  // First middle (default)

            🔁 Alternatively, you can also choose:
                median = houses[i + (j - i + 1) / 2];  // Second middle

            Both are valid and yield the same total cost.
            We typically choose the first middle for consistency and simplicity.
*/
// ***************************************** My Solution *****************************************
class Solution {
    public:
    int solveRec(int curr,int k,vector<vector<int>> &cost){
        int n=cost.size();
        if(curr==n && k==0) return 0;
        if(curr==n || k==0) return INT_MAX;

        long long int ans=INT_MAX;
        for(int i=curr;i<n;i++){
            ans=min(ans, 1LL * cost[curr][i]+solveRec(i+1,k-1,cost));
        }
        return ans;
    }



    int solveRec_Mem(int curr,int k,vector<vector<int>> &cost,vector<vector<int>> &dp){
        int n=cost.size();
        if(curr==n && k==0) return 0;
        if(curr==n || k==0) return INT_MAX;

        if(dp[curr][k]!=-1) return dp[curr][k];

        long long int ans=INT_MAX;
        for(int i=curr;i<n;i++){
            ans=min(ans, 1LL * cost[curr][i]+solveRec_Mem(i+1,k-1,cost,dp));
        }
        return dp[curr][k]=ans;
    }

    int minDistance(vector<int>& houses, int k) {
        int n=houses.size();
        vector<vector<int>> cost(n,vector<int>(n,0));
        sort(houses.begin(),houses.end());
        
        // Construct cost matrix
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){

                // finding cost for interval [i,j]
                int housesCount=(j-i+1);
                int median = houses[i + (housesCount / 2)];
                int currCost=0;
                for(int k=i;k<=j;k++) currCost+=abs(median-houses[k]);
                cost[i][j]=currCost;
            }
        }

        // Recursion
        // return solveRec(0,k,cost);

 
        // Recursion + Memoization
        vector<vector<int>> dp(n+1,vector<int>(k+1,-1));
        return solveRec_Mem(0,k,cost,dp);
    }
};
// ***************************************** My Solution *****************************************