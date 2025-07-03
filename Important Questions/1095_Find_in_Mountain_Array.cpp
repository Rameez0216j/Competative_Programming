/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */


// *************************************** My Solution ***************************************
class Solution {
    enum partitionType {
        INCREASING,
        DECREASING
    };

    public:
    int findPivot(MountainArray &mountainArr) {
        int low = 0;
        int high = mountainArr.length() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;
            int val = mountainArr.get(mid);
            int leftVal = mid > 0 ? mountainArr.get(mid - 1) : -1;
            int rightVal = mid < high ? mountainArr.get(mid + 1) : -1;

            if (leftVal < val && val < rightVal) {
                low = mid + 1;
            } else if (leftVal > val && val > rightVal) {
                high = mid - 1;
            } else {
                // Peak case
                if (val > leftVal && val > rightVal)
                    return mid;
                else
                    high = mid;
            }
        }

        return low;
    }

    int findEle(int target, int low, int high, partitionType t, MountainArray &mountainArr) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int val = mountainArr.get(mid);

            if (val == target) return mid;

            if (t == INCREASING) {
                if (target < val) high = mid - 1;
                else low = mid + 1;
            } else {
                if (target < val) low = mid + 1;
                else high = mid - 1;
            }
        }

        return -1;
    }

    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        int pivot = findPivot(mountainArr);

        int ind1 = findEle(target, 0, pivot, INCREASING, mountainArr);
        if (ind1 != -1) return ind1;
        return findEle(target, pivot + 1, n - 1, DECREASING, mountainArr);
    }
};
// *************************************** My Solution ***************************************
