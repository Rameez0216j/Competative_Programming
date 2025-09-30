// Used when array is infinite or very large.
int exponentialSearch(vector<int>& arr, int x) {
    if (arr[0] == x) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= x) i *= 2;
    return binarySearch(arr, i/2, min(i, arr.size()-1), x);
}
