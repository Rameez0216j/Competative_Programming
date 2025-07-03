// *************************************** My Solution ***************************************
class Solution {
    const int M = 1e9 + 7;

    // GCD using Euclidean Algorithm
    int GCD(int a, int b) {
        if (b == 0) return a;
        return GCD(b, a % b);
    }

    // Check if there are at least `n` magical numbers ≤ val
    bool isPossible(long long val, int a, int b, long long lcm_ab, int n) {
        long long divisibleByA = val / a;
        long long divisibleByB = val / b;
        long long divisibleByAB = val / lcm_ab;

        long long total_divisible = divisibleByA + divisibleByB - divisibleByAB;
        return total_divisible >= n;
    }

public:
    int nthMagicalNumber(int n, int a, int b) {
        long long low = min(a, b);
        long long high = 1e14;
        long long lcm_ab = (1LL * a * b) / GCD(a, b);

        long long ans = -1;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (isPossible(mid, a, b, lcm_ab, n)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans % M;
    }
};
// *************************************** My Solution ***************************************