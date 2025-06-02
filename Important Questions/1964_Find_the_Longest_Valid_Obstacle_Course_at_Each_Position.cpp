// **************************************** My solution LIS(TLE) ****************************************
/*
class Solution {
    public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n=obstacles.size();
        vector<int> LIS(n,1); // every individual element is a 1 length sub sequence

        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(obstacles[j]<=obstacles[i]){
                    LIS[i]=max(LIS[i],LIS[j]+1);
                }
            }
        }
        return LIS;
    }
};
*/
// **************************************** My solution LIS(TLE) ****************************************








// Solution : https://www.youtube.com/watch?v=sUtUgMW2kMY&t=683s
// *************************** My solution [LIS using binary search] ***************************
/*  
    tracker[i] = x ==> There exists a non-decreasing subsequence of length (i + 1) 
     where 'x' is the smallest possible ending element of such a subsequence.

     Why store the smallest possible end element?
     → To enable efficient binary search. 
     → Smaller ending values allow more future elements to be appended.

     Key Idea:
     - At each step, we try to place the current element at the right position
       in the tracker using upper_bound (because we allow non-decreasing order).
     - If the element is greater than or equal to all in the tracker, it extends the sequence.
     - Otherwise, it replaces the first element greater than itself to maintain optimal endings.

     LIS[i] = length of the longest valid (non-decreasing) subsequence ending at position i.
*/

class Solution {
    public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> tracker;  // Keeps smallest possible ending elements of increasing subsequences
        vector<int> LIS;      // Stores the answer for each position

        for (int i = 0; i < n; i++) {
            // Find the first element in tracker > obstacles[i]
            auto it = upper_bound(tracker.begin(), tracker.end(), obstacles[i]);

            int ind = it - tracker.begin(); // Index where this obstacle fits

            if (ind >= tracker.size()) {
                // If current obstacle is >= all in tracker, it extends the sequence
                tracker.push_back(obstacles[i]);   // O(log n) due to binary search
            } else {
                // Replace with smaller or equal to maintain smallest possible end element
                tracker[ind] = obstacles[i];
            }

            // Store length of LIS ending at index i
            LIS.push_back(ind + 1);
        }

        return LIS;
    }
};

// *************************** My solution [LIS using binary search] ***************************
