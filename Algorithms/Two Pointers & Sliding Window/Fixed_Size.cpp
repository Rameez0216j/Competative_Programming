/*
    Find longest subarray with sum ≤ K
*/

int maxSumSubarrayK(vector<int>& a, int k) {
    int sum = 0, maxSum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    maxSum = sum;
    for (int i = k; i < a.size(); i++) {
        sum += a[i] - a[i - k];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
