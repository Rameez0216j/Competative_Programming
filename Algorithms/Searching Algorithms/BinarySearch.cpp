/*
    Time: O(log n)
    Pre-condition: Sorted Array
*/


int binarySearch(vector<int>& a, int key) {
    int low = 0, high = a.size() - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (a[mid] == key) return mid;
        else if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
