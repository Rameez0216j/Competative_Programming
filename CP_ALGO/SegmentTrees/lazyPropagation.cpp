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

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];  // Apply lazy value
            if (start != end) {  // Not a leaf node
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // Range update: add val to all elements in [l, r]
    void updateRange(int l, int r, int val, int node, int start, int end) {
        push(node, start, end);

        if (r < start || end < l) return; // No overlap
        if (l <= start && end <= r) {     // Total overlap
            lazy[node] += val;
            push(node, start, end);
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


/*
Here push function is used to apply the lazy value to the current node and propagate it to its children if necessary.
This will only propagate the lazy value if it is not zero.

NOTE: WHY IS push FUNCTION CALLED IN ALL THE UPDATE AND QUERY FUNCTIONS?
push is called in all the update and query functions as we are going down the tree upto leaf nodes meaning we need to apply the lazy value to the current node and propagate it to its children if necessary.
*/