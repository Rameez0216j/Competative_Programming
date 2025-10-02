// Solution : https://www.youtube.com/watch?v=L-KWU8W3OqE
// ************************************* My Solution *************************************
class Solution
{
public:
    long long putMarbles(vector<int> &weights, int k)
    {
        int n = weights.size();
        vector<long long> pairSums;

        // Compute sums of adjacent weights
        for (int i = 1; i < n; i++)
        {
            pairSums.push_back(1LL * weights[i - 1] + weights[i]);
        }

        // Sort to easily pick smallest and largest (k-1) sums
        sort(pairSums.begin(), pairSums.end());

        long long maxSum = 0, minSum = 0;
        int totalPairs = pairSums.size();

        // Select (k-1) largest sums for max partition
        // Select (k-1) smallest sums for min partition
        for (int i = 0; i < k - 1; i++)
        {
            maxSum += pairSums[totalPairs - i - 1];
            minSum += pairSums[i];
        }

        return maxSum - minSum;
    }
};
// ************************************* My Solution *************************************

2551_Put_Marbles_in_Bags.cpp