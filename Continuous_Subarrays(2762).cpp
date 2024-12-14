// ********* My solution [Tracking max/min in window and 2 pointer] - Monotonic Deque *********

class Solution {
    public:
    long long continuousSubarrays(vector<int>& nums) {
        int i=0;
        int j=0;
        int n=nums.size();
        deque<int> maxi;
        deque<int> mini;

        long long int ans=0;
        while(j<n){
            // tracking maximum value 
            while(!maxi.empty() && nums[maxi.back()]<nums[j]) maxi.pop_back();
            maxi.push_back(j);
            
            // tracking minimum value
            while(!mini.empty() && nums[mini.back()]>nums[j]) mini.pop_back();
            mini.push_back(j);

            int max_val=nums[maxi.front()];
            int min_val=nums[mini.front()];
            while((max_val-min_val) > 2){
                if(maxi.front()==i) maxi.pop_front();
                if(mini.front()==i) mini.pop_front();
                i++;

                max_val=nums[maxi.front()];
                min_val=nums[mini.front()];
            }

            ans+=1LL*(j-i+1);
            j++;
        }

        return ans;
    }
};

// ********* My solution [Tracking max/min in window and 2 pointer] - Monotonic Deque *********


// ************************************** [Sorted Map] **************************************
/*
The end() function returns an iterator that points to one past the last element of a container.

The rend() function returns a reverse iterator that points to the theoretical element before the first element of the container.
*/
/*
class Solution {
    public:
    long long continuousSubarrays(vector<int>& nums) {
        int i=0;
        int j=0;
        int n=nums.size();
        map<int,int> freq;

        long long int ans=0;
        while(j<n){
            freq[nums[j]]++;

            int min_ele=freq.begin()->first;
            int max_ele=freq.rbegin()->first;
            while((max_ele - min_ele) > 2){
                freq[nums[i]]--;
                if(freq[nums[i]]==0) freq.erase(nums[i]);
                i++;

                min_ele=freq.begin()->first;
                max_ele=freq.rbegin()->first;
            }

            ans+=1LL*(j-i+1);
            j++;
        }

        return ans;
    }
};
*/
// ************************************** [Sorted Map] **************************************


// ************************************ [Priority Queue] ************************************
/*
class Solution {
    public:
    long long continuousSubarrays(vector<int>& nums) {
        int left = 0, right = 0;
        long long count = 0;  // Total count of valid subarrays

        // Min and max heaps storing indices, sorted by nums[index] values
        priority_queue<int, vector<int>, function<bool(int, int)>> minHeap(
            [&nums](int a, int b) { return nums[a] > nums[b]; });
        priority_queue<int, vector<int>, function<bool(int, int)>> maxHeap(
            [&nums](int a, int b) { return nums[a] < nums[b]; });

        while (right < nums.size()) {
            // Add current index to both heaps
            minHeap.push(right);
            maxHeap.push(right);

            // While window violates |nums[i] - nums[j]| ≤ 2 condition
            // Shrink window from left and remove outdated indices
            while (left < right &&
                   nums[maxHeap.top()] - nums[minHeap.top()] > 2) {
                left++;

                // Remove indices that are now outside window
                while (!maxHeap.empty() && maxHeap.top() < left) {
                    maxHeap.pop();
                }
                while (!minHeap.empty() && minHeap.top() < left) {
                    minHeap.pop();
                }
            }

            // Add count of all valid subarrays ending at right
            count += right - left + 1;
            right++;
        }

        return count;
    }
};
*/
// ************************************ [Priority Queue] ************************************



// ************************************ [Two Pointers] ************************************
/*
class Solution {
    public:
    long long continuousSubarrays(vector<int>& nums) {
        int right = 0, left = 0;
        int curMin, curMax;
        long long windowLen = 0, total = 0;

        // Initialize window with the first element
        curMin = curMax = nums[right];

        for (right = 0; right < nums.size(); right++) {
            // Update min and max for the current window
            curMin = min(curMin, nums[right]);
            curMax = max(curMax, nums[right]);

            // If window condition breaks (diff > 2)
            if (curMax - curMin > 2) {
                // Add subarrays from the previous valid window
                windowLen = right - left;
                total += (windowLen * (windowLen + 1) / 2);

                // Start a new window at the current position
                left = right;
                curMin = curMax = nums[right];

                // Expand left boundary while maintaining the condition
                while (left > 0 && abs(nums[right] - nums[left - 1]) <= 2) {
                    left--;
                    curMin = min(curMin, nums[left]);
                    curMax = max(curMax, nums[left]);
                }

                // Remove overcounted subarrays if left boundary expanded
                if (left < right) {
                    windowLen = right - left;
                    total -= (windowLen * (windowLen + 1) / 2);
                }
            }
        }

        // Add subarrays from the final window
        windowLen = right - left;
        total += (windowLen * (windowLen + 1) / 2);

        return total;
    }
};
*/
// ************************************ [Two Pointers] ************************************
