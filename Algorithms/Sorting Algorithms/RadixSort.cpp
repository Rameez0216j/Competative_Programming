/*
    Time: O(nk) where k = #digits
    Use: Sorting integers by digits (base 10 or base 256)
*/

int getMax(vector<int>& a) {
    return *max_element(a.begin(), a.end());
}

void countingSortByDigit(vector<int>& a, int exp) {
    int n = a.size();
    vector<int> output(n), count(10, 0);

    for (int i = 0; i < n; i++) count[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = n - 1; i >= 0; i--)
        output[--count[(a[i] / exp) % 10]] = a[i];

    a = output;
}

void radixSort(vector<int>& a) {
    for (int exp = 1; getMax(a) / exp > 0; exp *= 10)
        countingSortByDigit(a, exp);
}
