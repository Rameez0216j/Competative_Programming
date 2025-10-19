// Solution : https://www.youtube.com/watch?v=-SWrz90jCUM
// Variant of Leetcode 560 
// ******************************** My Solution [Prefix Sum] ********************************
class Solution {
    public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int numRows = matrix.size();
        int numCols = matrix[0].size();

        // Step 1: Compute row-wise prefix sums
        for (int r = 0; r < numRows; ++r) {
            for (int c = 1; c < numCols; ++c) {
                matrix[r][c] += matrix[r][c - 1];
            }
        }

        int count = 0;

        // Step 2: Fix two column boundaries (left and right)
        for (int left = 0; left < numCols; ++left) {
            for (int right = left; right < numCols; ++right) {
                unordered_map<int, int> prefixCount;
                prefixCount[0] = 1; // base case for sum=target

                int currentSum = 0;

                // Step 3: Apply subarray sum logic on row sums
                for (int row = 0; row < numRows; ++row) {
                    // Sum of elements in current row between columns [left, right]
                    int rowSum = matrix[row][right] - (left > 0 ? matrix[row][left - 1] : 0);

                    currentSum += rowSum;

                    // Check if there's a prefix subarray that leads to currentSum - target
                    if (prefixCount.count(currentSum - target)) {
                        count += prefixCount[currentSum - target];
                    }

                    prefixCount[currentSum]++;
                }
            }
        }

        return count;
    }
};
// ******************************** My Solution [Prefix Sum] ********************************