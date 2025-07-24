/*
    ============================
    TIME COMPLEXITY ANALYSIS
    ============================

    Let:
    - n = length of the target string (maximum 15)
    - m = total number of stickers

    --------------------------------------------------
    1. Number of Unique States → O(2^n)
    --------------------------------------------------
    - The recursive state is defined by the characters still needed in the target string (remTarget).
    - Each of the n characters can either:
        → Be already satisfied (absent from remTarget)
        → Still be required (present in remTarget)
    - This gives 2 options per character → 2^n total subsets of target characters.
    - So the maximum number of unique remTarget states is O(2^n).

    --------------------------------------------------
    2. Work Done per State → O(m)
    --------------------------------------------------
    - For each unique remTarget, we try applying all m stickers.
    - For each sticker:
        → We compute a new target by subtracting its character frequency (O(26) = constant)
        → Then we recurse on the new target
    - Thus, work done per remTarget is O(m).

    --------------------------------------------------
    3. Total Time Complexity → O(m * 2^n)
    --------------------------------------------------
    - Since there are at most O(2^n) unique remTarget states,
      and for each we try O(m) stickers:

        => Total Time = O(m * 2^n)

    --------------------------------------------------
    Additional Notes:
    --------------------------------------------------
    - This exponential time is feasible in practice because:
        → n ≤ 15, so 2^15 = 32,768 states
        → Memoization ensures each state is solved only once
        → Pruning (skipping unhelpful stickers) reduces unnecessary work

*/

// ***************************************** My solution *****************************************
class Solution {
    public:
    int solveRec(string target,vector<vector<int>> &stickerFreq){
        if(target.size()==0) return 0;
        int n=stickerFreq.size(); // total Stickers

        vector<int> targerFreq(26,0);
        for(char ch:target) targerFreq[ch-'a']++;

        int ans=INT_MAX;
        for(int i=0;i<n;i++){
            if(stickerFreq[i][target[0]-'a']==0) continue; // do not select

            string new_target="";
            for(int j=0;j<26;j++){
                int rem=targerFreq[j]-stickerFreq[i][j];
                for(int k=0;k<max(0,rem);k++){
                    new_target+=('a'+j);
                }
            }

            int next=solveRec(new_target,stickerFreq);
            if(next!=-1){
                ans=min(ans,1+next);
            }
        }
        return ans==INT_MAX ? -1 : ans;
    }


    int solveRec_Mem(string target,vector<vector<int>> &stickerFreq,unordered_map<string,int> &dp){
        int n=stickerFreq.size(); // total Stickers

        if(dp.count(target)) return dp[target];

        vector<int> targerFreq(26,0);
        for(char ch:target) targerFreq[ch-'a']++;

        int ans=INT_MAX;
        for(int i=0;i<n;i++){
            if(stickerFreq[i][target[0]-'a']==0) continue; // do not select

            string new_target="";
            for(int j=0;j<26;j++){
                int rem=targerFreq[j]-stickerFreq[i][j];
                for(int k=0;k<max(0,rem);k++){
                    new_target+=('a'+j);
                }
            }

            int next=solveRec_Mem(new_target,stickerFreq,dp);
            if(next!=-1){
                ans=min(ans,1+next);
            }
        }
        return dp[target]= ans==INT_MAX ? -1 : ans;
    }

    int minStickers(vector<string>& stickers, string target) {
        vector<vector<int>> stickerFreq;
        for(string sticker : stickers){
            vector<int> freq(26,0);
            for(char ch:sticker)  freq[ch-'a']++;
            stickerFreq.push_back(freq);
        }

        // Recursion
        // return solveRec(target,stickerFreq);


        // Recursion
        unordered_map<string,int> dp;
        dp[""]=0; // 0 stickers needed for empty target
        return solveRec_Mem(target,stickerFreq,dp);
    }
};
// ***************************************** My solution *****************************************



// ***************************************** My solution [with notes] *****************************************
/*
class Solution {
    public:

    // ---------------------------------------------
    // ✅ Recursive Solution (No Memoization)
    // Time Complexity: Exponential (TLE for large input)
    // ---------------------------------------------
    int solveRec(string target, vector<vector<int>> &stickerFreq) {
        // Base case: no characters left to build
        if (target.size() == 0) return 0;

        int n = stickerFreq.size(); // Total stickers
        vector<int> targetFreq(26, 0);

        // Build frequency map for the current target
        for (char ch : target) targetFreq[ch - 'a']++;

        int ans = INT_MAX;

        // Try using each sticker
        for (int i = 0; i < n; i++) {
            // Optimization: skip sticker if it doesn't have target[0]
            if (stickerFreq[i][target[0] - 'a'] == 0) continue;

            // Build new target after applying sticker[i]
            string new_target = "";
            for (int j = 0; j < 26; j++) {
                int rem = targetFreq[j] - stickerFreq[i][j];
                for (int k = 0; k < max(0, rem); k++) {
                    new_target += ('a' + j);
                }
            }

            // Recurse on the reduced target
            int next = solveRec(new_target, stickerFreq);
            if (next != -1) {
                ans = min(ans, 1 + next);
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }

    // --------------------------------------------------
    // ✅ Optimized Recursive + Memoization (Top-Down DP)
    // Time Complexity: O(m * 2^n)
    //   - m = total number of stickers
    //   - n = length of target string (≤ 15)
    // Explanation:
    //   - There are at most 2^n different remaining target strings
    //   - For each, we try all m stickers → m * 2^n
    // --------------------------------------------------
    int solveRec_Mem(string target, vector<vector<int>> &stickerFreq, unordered_map<string, int> &dp) {
        int n = stickerFreq.size(); // Total stickers

        // Memoization check
        if (dp.count(target)) return dp[target];

        vector<int> targetFreq(26, 0);
        for (char ch : target) targetFreq[ch - 'a']++;

        int ans = INT_MAX;

        // Try applying each sticker
        for (int i = 0; i < n; i++) {
            // Optimization: skip if sticker doesn't have first char of target
            if (stickerFreq[i][target[0] - 'a'] == 0) continue;

            // Build reduced target after using current sticker
            string new_target = "";
            for (int j = 0; j < 26; j++) {
                int rem = targetFreq[j] - stickerFreq[i][j];
                for (int k = 0; k < max(0, rem); k++) {
                    new_target += ('a' + j);
                }
            }

            int next = solveRec_Mem(new_target, stickerFreq, dp);
            if (next != -1) {
                ans = min(ans, 1 + next);
            }
        }

        // Memoize and return the result
        return dp[target] = (ans == INT_MAX ? -1 : ans);
    }

    // --------------------------------------------------
    // 🔰 Driver Function
    // --------------------------------------------------
    int minStickers(vector<string>& stickers, string target) {
        // Preprocess all stickers into frequency maps
        vector<vector<int>> stickerFreq;
        for (string sticker : stickers) {
            vector<int> freq(26, 0);
            for (char ch : sticker) freq[ch - 'a']++;
            stickerFreq.push_back(freq);
        }

        // 🛑 Brute force recursion (TLE for large inputs)
        // return solveRec(target, stickerFreq);

        // ✅ Optimized recursion with memoization
        unordered_map<string, int> dp;
        dp[""] = 0; // Base case: no stickers needed for empty target
        return solveRec_Mem(target, stickerFreq, dp);
    }
};
*/
// ***************************************** My solution [with notes] *****************************************