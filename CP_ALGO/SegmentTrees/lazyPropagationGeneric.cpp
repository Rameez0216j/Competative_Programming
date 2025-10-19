#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LazySegmentTree {
    vector<T> tree, lazy;
    int n;
    const T NEUTRAL = 0;  // Change as per operation: 0 for sum, ∞ for min, etc.

public:
    LazySegmentTree(vector<T>& arr) {
        n = arr.size();
        tree.resize(4 * n, NEUTRAL);
        lazy.resize(4 * n, 0);  // Change this if using range set instead of add
        build(arr, 0, 0, n - 1);
    }

    void build(vector<T>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            apply(node, start, end, lazy[node]);
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];  // Change logic for assignment update
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void apply(int node, int start, int end, T val) {
        tree[node] += (end - start + 1) * val;  // For sum query. Change logic for other ops.
    }

    T combine(T a, T b) {
        return a + b;  // For sum query. Use min(a,b), max(a,b), etc. as needed.
    }

    void updateRange(int l, int r, T val, int node, int start, int end) {
        push(node, start, end);

        if (r < start || end < l) return;  // No overlap
        if (l <= start && end <= r) {      // Total overlap
            lazy[node] += val;
            push(node, start, end);
            return;
        }

        // Partial overlap
        int mid = (start + end) / 2;
        updateRange(l, r, val, 2 * node + 1, start, mid);
        updateRange(l, r, val, 2 * node + 2, mid + 1, end);
        tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void updateRange(int l, int r, T val) {
        updateRange(l, r, val, 0, 0, n - 1);
    }

    T queryRange(int l, int r, int node, int start, int end) {
        push(node, start, end);

        if (r < start || end < l) return NEUTRAL;  // No overlap
        if (l <= start && end <= r) return tree[node]; // Total overlap

        int mid = (start + end) / 2;
        T left = queryRange(l, r, 2 * node + 1, start, mid);
        T right = queryRange(l, r, 2 * node + 2, mid + 1, end);
        return combine(left, right);
    }

    T queryRange(int l, int r) {
        return queryRange(l, r, 0, 0, n - 1);
    }
};






// for int type update code is as below
#include <iostream>
#include <vector>
using namespace std;

class LazySegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void apply(int node, int start, int end, int val) {
        // Apply value to the segment represented by the node
        tree[node] += (end - start + 1) * val;
        if (start != end) { // If not a leaf node, propagate lazily
            lazy[2 * node + 1] += val;
            lazy[2 * node + 2] += val;
        }
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            apply(node, start, end, lazy[node]);
            lazy[node] = 0;
        }
    }

    // Range update: add val to all elements in [l, r]
    void updateRange(int l, int r, int val, int node, int start, int end) {
        push(node, start, end);

        if (r < start || end < l) return; // No overlap
        if (l <= start && end <= r) {     // Total overlap
            apply(node, start, end, val);
            return;
        }

        // Partial overlap
        int mid = (start + end) / 2;
        updateRange(l, r, val, 2 * node + 1, start, mid);
        updateRange(l, r, val, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void updateRange(int l, int r, int val) {
        updateRange(l, r, val, 0, 0, n - 1);
    }

    // Range query: sum in [l, r]
    int queryRange(int l, int r, int node, int start, int end) {
        push(node, start, end);

        if (r < start || end < l) return 0;  // No overlap
        if (l <= start && end <= r) return tree[node]; // Total overlap

        // Partial overlap
        int mid = (start + end) / 2;
        int leftSum = queryRange(l, r, 2 * node + 1, start, mid);
        int rightSum = queryRange(l, r, 2 * node + 2, mid + 1, end);
        return leftSum + rightSum;
    }

    int queryRange(int l, int r) {
        return queryRange(l, r, 0, 0, n - 1);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    LazySegmentTree st(arr);

    cout << "Sum of range [1, 3]: " << st.queryRange(1, 3) << endl; // 3+5+7 = 15

    st.updateRange(1, 3, 3); // Add 3 to elements from index 1 to 3

    cout << "After update, sum of range [1, 3]: " << st.queryRange(1, 3) << endl; // 6+8+10 = 24

    cout << "Sum of range [0, 5]: " << st.queryRange(0, 5) << endl;

    return 0;
}

