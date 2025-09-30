/*
    🧠 Pattern:
    Used when: You are not searching an exact element

    Instead, searching for the smallest/largest value that satisfies a condition

    Example problem: Minimum number of days required to make m bouquets.
*/


int minDays(vector<int>& bloomDay, int m, int k) {
    int low = 1, high = 1e9, ans = -1;
    auto canMake = [&](int days) {
        int count = 0, flowers = 0;
        for (int b : bloomDay) {
            if (b <= days) {
                flowers++;
                if (flowers == k) {
                    count++;
                    flowers = 0;
                }
            } else flowers = 0;
        }
        return count >= m;
    };
    
    while (low <= high) {
        int mid = (low + high)/2;
        if (canMake(mid)) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    return ans;
}


/*
    Time: O(n log(max(bloomDay)))
    Space: O(1)
    Use: Searching for the minimum number of days to satisfy a condition
    Pre-condition: bloomDay array is non-negative integers

    ✅ Used in:
        Aggressive cows
        Allocate books
        EKO SPOJ
        Painter Partition
        Koko Eating Bananas
        Minimum number of days to make m bouquets
        Minimum time required to finish all jobs
        Minimum number of platforms required for a railway station
        Maximum number of tasks that can be completed in a given time
        Maximum number of tasks that can be completed with given resources
        Maximum number of tasks that can be completed with given constraints
        Minimum number of days to complete a project
        Minimum number of days to complete a task   
*/


// C++ STL methods for binary search
int idx = lower_bound(a.begin(), a.end(), x) - a.begin();  // First index ≥ x
int idx = upper_bound(a.begin(), a.end(), x) - a.begin();  // First index > x
