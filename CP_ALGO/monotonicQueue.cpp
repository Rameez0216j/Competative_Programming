/*
Monotonic Queue Approach for Circular Gas Station Problem

Problem:
- You have `n` gas stations in a circle.
- `gas[i]` = gas available at station i
- `cost[i]` = gas required to travel from station i to i+1
- Find starting station to complete the circle, or -1 if impossible

Key Idea:
- Compute prefix sum of net gas (gas - cost)
- Use a **monotonic queue** to efficiently find the minimum prefix in a sliding window of size n
- Monotonic queue keeps indices of increasing prefix sums
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        vector<int> netGasPrefix; // prefix sum of net gas
        int sum = 0;

        // Compute prefix sums for 2 rotations (simulate circular array)
        for (int i = 0; i < 2 * n; i++) {
            sum += gas[i % n] - cost[i % n];
            netGasPrefix.push_back(sum);
        }
        // Most Important Note : for an answer to exist there should always be a window length of size n which has values in increasing order

        // Monotonic queue to find minimum prefix in window of size n
        deque<int> monoQueue; // stores indices
        for (int i = 0; i < netGasPrefix.size(); i++) {
            // Maintain increasing order in the queue (monotonic indices)
            while (!monoQueue.empty() && netGasPrefix[monoQueue.back()] > netGasPrefix[i]) {
                monoQueue.pop_back();
            }

            // Check if the front of queue is outside the window
            if (!monoQueue.empty() && i - monoQueue.front() >= n) {
                return (monoQueue.front() + 1) % n; // starting station
            }

            monoQueue.push_back(i);
        }

        return -1; // no valid starting station
    }
};












/*
Problem: Shortest Subarray with Sum at Least K
Given an array nums[], find the length of the shortest contiguous subarray
with sum >= K. Return -1 if no such subarray exists.

Key Idea:
1. Compute prefix sum: prefixSum[i] = sum of nums[0..i-1]
2. Use a monotonic queue to maintain candidate start indices for subarrays.
   - Queue stores indices in increasing order of prefixSum
3. For each current prefixSum[i], check if prefixSum[i] - prefixSum[queue.front()] >= K
   - If yes, we found a valid subarray, pop from front and update answer
4. Maintain monotonicity:
   - If current prefixSum is smaller than prefixSum[queue.back()], pop back
     (smaller prefixSum is better as start of subarray)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int K) {
        int n = nums.size();
        vector<long long> prefixSum(n + 1, 0);
        
        // Compute prefix sums
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        int answer = n + 1; // initialize with impossible large value
        deque<int> dq; // stores indices of prefixSum in increasing order

        for (int i = 0; i <= n; i++) {
            // Check front of queue for valid subarray
            while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= K) {
                answer = min(answer, i - dq.front());
                dq.pop_front();
            }

            // Maintain monotonicity of prefixSum in the queue
            while (!dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i); // add current index as candidate start
        }

        return (answer <= n) ? answer : -1;
    }
};
