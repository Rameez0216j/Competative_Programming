#include <vector>
using namespace std;

int findPeakElement(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;

        // Compare with the next element to decide the direction
        if (arr[mid] < arr[mid + 1]) {
            // You're in the increasing part of the mountain
            low = mid + 1;
        } else {
            // You're in the decreasing part of the mountain
            high = mid;
        }
    }

    // low == high is the peak
    return low;
}
