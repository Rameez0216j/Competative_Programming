/*
    Use case: Find longest subarray with sum ≤ K
*/

int longestSubarraySumLEK(vector<int>& a, int k) {
    int i = 0, sum = 0, ans = 0;
    for (int j = 0; j < a.size(); j++) {
        sum += a[j];
        while (sum > k) sum -= a[i++];
        ans = max(ans, j - i + 1);
    }
    return ans;
}
