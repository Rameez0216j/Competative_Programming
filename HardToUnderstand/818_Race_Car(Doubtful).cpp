class Solution {
    public:
    int racecar(int target) {
        std::vector<int> dp(target + 1, -1);
        return dfs(target, dp);
    }

    int dfs(int target, std::vector<int>& dp) {
        if (dp[target] != -1) return dp[target];
        int min_steps = INT_MAX;

        // Try all k such that (2^k - 1) is the distance after k 'A' instructions
        for (int k = 1; ; ++k) {
            int distance_after_k_A = (1 << k) - 1;

            if (distance_after_k_A == target) {
                min_steps = k;  // Reached exactly with k accelerations
                break;
            }

            if (distance_after_k_A > target) {
                // Overshoot: reverse and come back
                min_steps = std::min(min_steps,
                                    k + 1 + dfs(distance_after_k_A - target, dp));
                break;
            }

            // Undershoot: move k steps, reverse, go back p steps (0 ≤ p < k)
            for (int p = 0; p < k; ++p) {
                int distance_back = (1 << p) - 1;
                int remaining = target - (distance_after_k_A - distance_back); // this never goes to negative

                // k A + 1 R + p A + 1 R + recurse
                int steps = k + 1 + p + 1 + dfs(remaining, dp);
                min_steps = std::min(min_steps, steps);
            }
        }

        return dp[target] = min_steps;
    }
};
