/*
    Time: O(n^2)
    Stable: ❌
    Space: O(1)
*/
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
}
