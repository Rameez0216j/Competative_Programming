/*
    Time: O(n log n) avg, O(n^2) worst
    Stable: ❌
    Space: O(log n)
*/

int partition(vector<int>& a, int low, int high) {
    int pivot = a[high], i = low;
    for (int j = low; j < high; j++)
        if (a[j] < pivot)
            swap(a[i++], a[j]);
    swap(a[i], a[high]);
    return i;
}

void quickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
