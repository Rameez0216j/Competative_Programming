// Solution : https://www.youtube.com/watch?v=NsJXKLc8Dso
/*
    ╔══════════════════════════════════════════════════════╗
    ║       🚗 WHY WE USE A LAP TIME THRESHOLD (2e8)       ║
    ╚══════════════════════════════════════════════════════╝

    📌 Problem Summary:
    ---------------------
    Given:
    - Each tire has:
        • fᵢ = initial lap time (1 ≤ fᵢ ≤ 1e5)
        • rᵢ = rate of lap time growth (2 ≤ rᵢ ≤ 1e5)
    - changeTime = penalty for switching tires (≤ 1e5)
    - numLaps = number of laps to finish the race (≤ 1000)

    Goal: 
    → Finish all laps in minimum time by choosing when to 
    reuse tires or switch them.

    🧠 Tire Usage:
    --------------
    When a tire is reused without switching, its lap time grows:
        Lap 1: fᵢ
        Lap 2: fᵢ * rᵢ
        Lap 3: fᵢ * rᵢ²
        ...
        Lap k: fᵢ * rᵢ⁽ᵏ⁻¹⁾

    This grows **exponentially** and becomes impractically large fast.

    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    💥 Worst-Case Total Time Estimation:
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    Assume:
    - Every tire has fᵢ = 1e5 (worst case)
    - changeTime = 1e5
    - You switch tire after every lap (most expensive strategy)

    Then:
    - Lap time for 1000 laps = 1000 × 1e5 = 1e8
    - Tire switch time for 999 switches = 999 × 1e5 ≈ 1e8
    - Total time = 1e8 + 1e8 = **2e8**

    So, the **entire race** can always be finished in ≤ 2e8 time.

    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    🔒 Why We Use a Threshold in the Code:
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    As lap times increase exponentially, we want to stop simulating
    once lap time becomes too large to ever be part of an optimal solution.

    If any single lap takes more than 2e8 time:
    → it's worse than just switching tires and restarting.

    ✅ So we add a cutoff:
        if ((long long)lapTime > 2e8) break;

    This ensures:
    - We avoid unnecessary recursive calls
    - We stay within realistic bounds
    - We don’t simulate useless long lap sequences

    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    🎯 Key Takeaway:
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    🟢 No lap time > 2e8 will ever appear in the optimal solution  
    🟢 2e8 is the **tightest upper bound** derived directly from constraints  
    🟢 It's better than arbitrary large values like 1e9  
    🟢 Keeps solution fast, safe, and correct

    Recommended:
        const long long MAX_LAP_TIME = 2e8;
        if ((long long)lapTime > MAX_LAP_TIME) break;
*/



// ********************************** My Solution - [TLE => Both rec and recMem] **********************************
/*
class Solution {
    public:
    vector<vector<int>> tires;
    int changeTime;

    int solveRec(int lapsLeft) {
        if(lapsLeft==0) return 0;

        int ans=INT_MAX;
        for(auto &tire:tires){
            int fi=tire[0];
            int ri=tire[1];

            int totalTime=0;
            int currLapTime=fi;
            for(int lap=1;lap<=lapsLeft;lap++){
                totalTime+=currLapTime;
                int remainingTime=solveRec(lapsLeft-lap);
                ans=min(ans,totalTime+changeTime+remainingTime);
                
                // No lap time > 2e8 will ever appear in the optimal solution  
                if((long long)currLapTime*ri >= 2e8) break;

                currLapTime=currLapTime*ri;
            }
        }

        return ans;
    }



    int solveRec_Mem(int lapsLeft,vector<int> &dp) {
        if(lapsLeft==0) return 0;

        if(dp[lapsLeft]!=-1) return dp[lapsLeft];

        int ans=INT_MAX;
        for(auto &tire:tires){
            int fi=tire[0];
            int ri=tire[1];

            int totalTime=0;
            int currLapTime=fi;
            for(int lap=1;lap<=lapsLeft;lap++){
                totalTime+=currLapTime;
                int remainingTime=solveRec_Mem(lapsLeft-lap,dp);
                ans=min(ans,totalTime+changeTime+remainingTime);
                
                // No lap time > 2e8 will ever appear in the optimal solution  
                if((long long)currLapTime*ri >= 2e8) break;
                
                currLapTime=currLapTime*ri;
            }
        }

        return dp[lapsLeft]=ans;
    }

    int minimumFinishTime(vector<vector<int>>& tires_, int changeTime_, int numLaps) {
        // NOTE :  Recursion is ending at lapsLeft==0 before reaching it we are doing ==> totalTime+changeTime+remainingTime so we subtract changeTime from ans as last tire needs no changing

        // Recursion
        // tires = tires_;
        // changeTime = changeTime_;
        // return solveRec(numLaps) - changeTime;  // subtract changeTime after last lap


        // Recursion + Memoization
        tires = tires_;
        changeTime = changeTime_;
        vector<int> dp(numLaps+1,-1);
        return solveRec_Mem(numLaps,dp) - changeTime;  // subtract changeTime after last lap 
    }
};
*/
// ********************************** My Solution - [TLE => Both rec and recMem] **********************************







// ********************************** Solution [Optimized] **********************************
/*
    🔧 Problem Optimization Insight:

    In the original approach, for each recursive call, we simulate using the same tire for multiple consecutive laps:
        - For example, using tire T for 1 lap, 2 laps, 3 laps, ..., k laps
        - Each time, we recalculate lap times like: f, f*r, f*r^2, ..., f*r^(k-1)

    ❌ But this is inefficient because:
        - We might compute the same tire sequence repeatedly in multiple recursion paths.
        - We might even switch to the same type of tire again later, and recalculate its entire sequence again.
        - Why not avoid this and precompute a streak array instead of simulating every tire every time?

    ✅ Optimization:
    ---------------------
    To avoid recomputation, we **precompute a streak table**:

    🧩 streak[k] = the minimum time required to complete exactly `k` consecutive laps 
                using any single tire without switching.

    📌 Note:
    - This is independent of *which* tire we use.
    - We only care about the **fastest** way to complete `k` consecutive laps with any tire.

    🏁 Now the problem becomes:
    ------------------------------
    ➡️ We are given this `streak[]` array.
    ➡️ We want to choose a combination of such streaks (of 1..k laps), 
        so that their total adds up to `numLaps`.
    ➡️ Our goal is to minimize the **total time**, which includes:
        - Sum of selected streak times
        - Plus `changeTime` for switching between streaks

    📌 This reduces the problem to a classic DP:
        - At each step, we try all possible streak sizes.
        - We update dp[i] as the minimum time to complete `i` laps.

    This transformation makes the solution far more efficient and avoids redundant exponential-time calculations.
*/

class Solution {
public:
    vector<vector<int>> tires;
    int changeTime;
    int numLaps;

    // Store best time to run k laps without switching tires
    vector<int> minTimePerStreak;

    int solveRec_Mem(int lapsLeft, vector<int>& dp) {
        if (lapsLeft == 0) return 0;
        if (dp[lapsLeft] != -1) return dp[lapsLeft];

        int ans = INT_MAX;

        // Try all streak sizes from 1 to lapsLeft
        for (int streak = 1; streak <= lapsLeft; ++streak) {
            if (minTimePerStreak[streak] == INT_MAX) continue; // impossible streak (No tyre is efficient for this streak) ==> pruning
            int remainingTime = solveRec_Mem(lapsLeft - streak, dp);
            ans = min(ans, minTimePerStreak[streak] + changeTime + remainingTime);
        }

        return dp[lapsLeft] = ans;
    }

    int minimumFinishTime(vector<vector<int>>& tires_, int changeTime_, int numLaps_) {
        tires = tires_;
        changeTime = changeTime_;
        numLaps = numLaps_;

        // Step 1: Precompute minTimePerStreak[1..numLaps]
        // Independent of tire type, we store minTimePerStreak[k] as the minimum time required to complete exactly k consecutive laps using the most efficient tire for that k laps.
        minTimePerStreak.assign(numLaps + 1, INT_MAX);

        for (auto& tire : tires) {
            int fi = tire[0];
            int ri = tire[1];

            long long currLapTime = fi;
            long long totalTime = 0;

            for (int lap = 1; lap <= numLaps; ++lap) {
                totalTime += currLapTime;
                if (totalTime > 2e8) break; // cutoff from previous reasoning
                minTimePerStreak[lap] = min(minTimePerStreak[lap], (int)totalTime);
                currLapTime *= ri;
                if (currLapTime > 2e8) break; // prevent overflow and useless cases
            }
        }

        // Step 2: DP with memoization
        vector<int> dp(numLaps + 1, -1);
        return solveRec_Mem(numLaps, dp) - changeTime; // subtract last changeTime
    }
};
// ********************************** Solution [Optimized] **********************************
