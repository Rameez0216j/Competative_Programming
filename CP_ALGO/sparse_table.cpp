/*
Sparse Table for Range Sum Queries:

Key Components:
a[i]           --> original array
st[i][j]       --> stores sum of subarray starting at i with length 2^j
log2[i]        --> precomputed floor(log2(i)) to quickly calculate interval length
n               --> size of array
Query(l, r)    --> compute sum of range [l, r]

Note: Sparse table works best for idempotent operations (min/max/gcd).
For sum queries, we usually combine it with prefix sums.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Precompute log2 values
    vector<int> log2(n + 1, 0);
    for (int i = 2; i <= n; ++i)
        log2[i] = log2[i / 2] + 1;

    int K = log2[n]; // maximum power of 2
    vector<vector<long long>> st(n, vector<long long>(K + 1, 0));

    // Initialize sparse table for length 1 intervals
    for (int i = 0; i < n; ++i) st[i][0] = a[i];

    // Build Sparse Table
    for (int j = 1; j <= K; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[i][j] = st[i][j - 1] + st[i + (1 << (j - 1))][j - 1];
        }
    }

    // Answering queries
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r; // 0-based indices

        long long sum = 0;
        for (int j = K; j >= 0; --j) {
            if ((1 << j) <= r - l + 1) {
                sum += st[l][j];
                l += (1 << j);
            }
        }

        cout << sum << "\n";
    }
}

/*
Tips and Tricks:

1. Pattern Recognition:
   - Problem asks for **static range sum queries** (no updates).
   - Range length may vary, and multiple queries are asked.
   - Sparse Table is perfect for static queries, especially min/max/gcd. For sums, prefix sum + sparse table can be used for O(1) queries if allowed.

2. Optimization Tips:
   - Precompute log2[] to quickly calculate largest power of 2 <= length of query interval.
   - Time complexity:
       - Preprocessing: O(n log n)
       - Query: O(log n) using powers of 2
   - Space complexity: O(n log n)

3. Hard LeetCode / CP Problems:
   - 307. Range Sum Query - Mutable (for comparison)
   - 303. Range Sum Query - Immutable
   - 307. Range Sum Query 2D - Mutable (2D variant)
   - CF / AtCoder: Many RMQ / RSQ problems use sparse table.
*/
