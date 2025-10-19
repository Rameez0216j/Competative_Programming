/*
Square Root Decomposition (Block Decomposition): 
Efficiently answers range sum queries (and updates) on an array.
Preprocesses the array in blocks of size sqrt(n) to speed up queries.

Key Components:
a[i]       --> original array
b[block]   --> precomputed sum of elements in each block
len        --> block size
l, r       --> query range
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Preprocessing
    int len = (int)sqrt(n + 0.0) + 1;  // block size
    int numBlocks = (n + len - 1) / len; 
    vector<int> blockSum(numBlocks, 0);

    for (int i = 0; i < n; ++i) {
        blockSum[i / len] += a[i]; // add element to its block sum
    }

    // Answering queries
    int q; 
    cin >> q; // number of queries
    while (q--) {
        int l, r;
        cin >> l >> r;  // 0-based index range [l, r]
        int sum = 0;

        int startBlock = l / len;
        int endBlock = r / len;

        if (startBlock == endBlock) {
            // Both l and r are in the same block: sum directly
            for (int i = l; i <= r; ++i) sum += a[i];
        } else {
            // Sum remaining elements in the first partial block
            for (int i = l; i < (startBlock + 1) * len; ++i) sum += a[i];

            // Sum whole blocks between startBlock+1 and endBlock-1
            for (int block = startBlock + 1; block <= endBlock - 1; ++block)
                sum += blockSum[block];

            // Sum remaining elements in the last partial block
            for (int i = endBlock * len; i <= r; ++i) sum += a[i];
        }

        cout << sum << "\n";
    }
}

/*
Tips and Tricks:

1. Pattern Recognition:
   - Problem asks for range queries (sum, min, max) on an array.
   - Updates may or may not be involved (then we adjust blockSum on updates).
   - Query time complexity: O(sqrt(n)), preprocessing: O(n).

2. Optimization Tips:
   - Always choose block size ≈ sqrt(n) for balanced performance.
   - Can be extended to support updates by updating block sums.
   - Works well for offline queries or partially online queries.

3. Hard LeetCode / CP Problems:
   - 307. Range Sum Query - Mutable (Segment tree alternative)
   - 675. Cut Off Trees for Golf Event (can use sqrt decomposition on rows)
   - 1531. String Compression II (query + update problems)
   - CF / AtCoder: Many range sum + update problems
*/
