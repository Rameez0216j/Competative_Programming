// Solution : https://www.youtube.com/watch?v=jvPdUisQh3M&t=678s
// ************************************  My Solution ************************************
/*
class Solution {
    public:
    int oddEvenJumps(vector<int>& arr) {
        int n=arr.size();
        vector<int> indices(n,0);
        iota(indices.begin(),indices.end(),0); // asigns value as 0,1,2,3... [index]

        // Sorting index based on ascending order of values, ascending order of index 
        auto comp1=[&](int i,int j){
            if(arr[i]==arr[j]) return i<j;
            else return arr[i]<arr[j];
        };

        // Sorting index based on descending order of values, ascending order of index 
        auto comp2=[&](int i,int j){
            if(arr[i]==arr[j]) return i<j;
            else return arr[i]>arr[j];
        };


        // Next Smaller Element (allowed if equal as per problem statement)
        vector<int> nextLargestSmallerIndex(n,-1);
        sort(indices.begin(),indices.end(),comp1);
        stack<int> st;
        for(int idx : indices){
            while(!st.empty() && idx > st.top()){
                nextLargestSmallerIndex[st.top()] = idx;
                st.pop();
            }
            st.push(idx);
        }



        // Next Greater Element (allowed if equal as per problem statement)
        vector<int> nextSmallestHigherIndex(n,-1);
        sort(indices.begin(),indices.end(),comp2);
        st=stack<int>();
        for(int idx : indices){
            while(!st.empty() && idx > st.top()){
                nextSmallestHigherIndex[st.top()] = idx;
                st.pop();
            }
            st.push(idx);
        }


        // Actual problem logic 
        vector<bool> oddJump(n,false),evenJump(n,false);
        oddJump[n-1]=true;
        evenJump[n-1]=true;

        for(int i=n-2;i>=0;i--){
            int odd=nextLargestSmallerIndex[i];
            int even=nextSmallestHigherIndex[i];
            if(odd!=-1) oddJump[i]=evenJump[odd];
            if(even!=-1) evenJump[i]=oddJump[even];
        }

        int count=0;
        for(int i=0;i<n;i++){
            if(oddJump[i]==true) count++;
        }
        return count;
    }
};
*/
// ************************************  My Solution ************************************










// ************************  My Solution [cleaned and documented] ************************
/*
    Problem: Odd-Even Jumps (LeetCode 975)

    Goal:
    - Starting from index i, you can perform:
      - Odd jump: jump to the smallest index j > i where arr[j] >= arr[i]
      - Even jump: jump to the smallest index j > i where arr[j] <= arr[i]
    - Return the count of starting indices from which you can reach the last index.

    Key Technique:
    - Precompute next possible jumps using monotonic stack + sorting of indices.
    - Use DP to check reachability.
*/

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();

        // indices = [0, 1, 2, ..., n-1]
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);

        /*
            STEP 1: Compute Next Higher Index (for odd jumps)
            - Sort indices by ascending values, then by index
            - Monotonic stack finds the "nearest greater/equal to the right"
        */
        auto ascendingComp = [&](int i, int j) {
            if (arr[i] == arr[j]) return i < j;  // tie-breaker: smaller index first
            return arr[i] < arr[j];
        };

        vector<int> nextHigher(n, -1);
        sort(indices.begin(), indices.end(), ascendingComp);
        {
            stack<int> st;
            for (int idx : indices) {
                // Maintain increasing index order in stack
                while (!st.empty() && idx > st.top()) {
                    nextHigher[st.top()] = idx;
                    st.pop();
                }
                st.push(idx);
            }
        }

        /*
            STEP 2: Compute Next Lower Index (for even jumps)
            - Sort indices by descending values, then by index
            - Monotonic stack finds the "nearest smaller/equal to the right"
        */
        auto descendingComp = [&](int i, int j) {
            if (arr[i] == arr[j]) return i < j;
            return arr[i] > arr[j];
        };

        vector<int> nextLower(n, -1);
        sort(indices.begin(), indices.end(), descendingComp);
        {
            stack<int> st;
            for (int idx : indices) {
                while (!st.empty() && idx > st.top()) {
                    nextLower[st.top()] = idx;
                    st.pop();
                }
                st.push(idx);
            }
        }

        /*
            STEP 3: Dynamic Programming
            - oddJump[i] = can we reach end starting with an odd jump from i?
            - evenJump[i] = can we reach end starting with an even jump from i?
            - Transition:
                oddJump[i] = evenJump[nextHigher[i]]
                evenJump[i] = oddJump[nextLower[i]]
        */
        vector<bool> oddJump(n, false), evenJump(n, false);
        oddJump[n - 1] = evenJump[n - 1] = true;  // base case: last index can reach itself

        for (int i = n - 2; i >= 0; i--) {
            if (nextHigher[i] != -1) oddJump[i] = evenJump[nextHigher[i]];
            if (nextLower[i] != -1) evenJump[i] = oddJump[nextLower[i]];
        }

        /*
            STEP 4: Count how many indices can reach the end via odd jumps
        */
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (oddJump[i]) count++;
        }

        return count;
    }
};

/*
    ---------------- NOTES ----------------
    1. Monotonic Stack Role:
       - Sort indices by value, then use a stack to assign "next jump".
       - Ensures smallest valid index to the right is chosen.

    2. Why Two Sorts?
       - Odd jumps require "next higher/equal" → sort ascending.
       - Even jumps require "next lower/equal" → sort descending.

    3. DP Insight:
       - odd[i] depends on even[nextHigher[i]]
       - even[i] depends on odd[nextLower[i]]
       - Base case: last index can always reach itself.

    4. Time Complexity: O(n log n)  (due to sorting twice)
       Space Complexity: O(n)
*/
// ************************  My Solution [cleaned and documented] ************************