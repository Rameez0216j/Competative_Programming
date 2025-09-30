// Solution : https://www.youtube.com/watch?v=RNYq7z6aUDI
// ******************************* My Solution *******************************
/*
class Solution {
public:
    const int MOD = 1e9 + 7;

    int solveRec(int ind, vector<int>& nums, vector<int> &suffixArray) {
        int n = nums.size();
        if (ind == n) return 0;

        int next = solveRec(ind + 1, nums, suffixArray);
        return suffixArray[ind] = (nums[ind] + 2LL * next % MOD) % MOD;
    }

    int sumOfPower(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        vector<int> suffixArray(n + 1, 0);

        int temp = solveRec(0, nums, suffixArray);

        // Rebuild suffixArray correctly with MOD
        for (int i = 0; i < n; i++) {
            suffixArray[i] = (nums[i] + suffixArray[i + 1]) % MOD;
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long x = nums[i];
            long long x2 = x * x % MOD;
            ans = (ans + x2 * suffixArray[i] % MOD) % MOD;
        }

        return ans;
    }
};
*/
// ******************************* My Solution *******************************




// ******************************* My Solution [Iterative] *******************************
// Without Mod
/*
class Solution {
    public:
    int sumOfPower(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // Sort in ascending order

        long long ans = 0;
        long long preSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            long long x = nums[i];
            long long power = x * x;
            long long total = x + preSum;
            ans = ans + (power * total);

            preSum = preSum * 2 + x;
        }

        return ans;
    }
};
*/


class Solution {
public:
    int sumOfPower(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        sort(nums.begin(), nums.end()); // Sort in ascending order

        long long ans = 0;
        long long preSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            long long x = nums[i];
            long long power = x * x % MOD;
            long long total = (x + preSum) % MOD;
            ans = (ans + (power * total) % MOD) % MOD;

            preSum = (preSum * 2 + x) % MOD;
        }

        return ans;
    }
};

// ******************************* My Solution [Iterative] *******************************