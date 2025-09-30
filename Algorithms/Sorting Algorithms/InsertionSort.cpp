/*
    Time: O(n^2)
    Stable: ✅
    Best Case: O(n) (nearly sorted)
*/


void insertionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key)
            a[j + 1] = a[j--];
        a[j + 1] = key;
    }
}
