/*
    Time: O(n^2)
    Space: O(1)
    Stable: ✅
    Use: Rare in CP, but great for educational purposes.
*/
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < n-i-1; ++j)
            if (a[j] > a[j+1])
                swap(a[j], a[j+1]);
}
