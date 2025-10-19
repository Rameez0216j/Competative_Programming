// Kadanes Algorithm

#include <bits/stdc++.h>
using namespace std;

int maxSumSubarray(vector<int>& arr) {
    int maxSum = arr[0];
    int currentSum = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        currentSum = max(arr[i], currentSum + arr[i]); // start new subarray or extend
        maxSum = max(maxSum, currentSum);            // update maxSum
    }

    return maxSum;
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Sum Subarray: " << maxSumSubarray(arr) << endl;
}
