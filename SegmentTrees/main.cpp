#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n); // Safe size
        build(arr, 0, 0, n - 1);
    }

    // Build the segment tree
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

    // Update index to new value
    void update(int idx, int val, int node, int start, int end) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(idx, val, 2 * node + 1, start, mid);
            else
                update(idx, val, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    // Public update method
    void update(int idx, int val) {
        update(idx, val, 0, 0, n - 1);
    }

    // Query sum in range [l, r]
    int query(int l, int r, int node, int start, int end) {
        if (r < start || l > end) return 0;        // No overlap
        if (l <= start && end <= r) return tree[node]; // Total overlap
        int mid = (start + end) / 2;
        int leftSum = query(l, r, 2 * node + 1, start, mid);
        int rightSum = query(l, r, 2 * node + 2, mid + 1, end);
        return leftSum + rightSum;
    }

    // Public query method
    int query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Sum of range [1, 3]: " << st.query(1, 3) << endl; // 3 + 5 + 7 = 15

    st.update(1, 10); // arr[1] = 10

    cout << "After update, sum of range [1, 3]: " << st.query(1, 3) << endl; // 10 + 5 + 7 = 22

    return 0;
}
