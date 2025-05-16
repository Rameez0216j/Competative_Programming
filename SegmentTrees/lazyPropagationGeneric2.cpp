#include <bits/stdc++.h>
using namespace std;

/* ---------------- Node Class ---------------- */
class Node {
public:
    int v = 0;

    Node() {}
    Node(int val) {
        v = val;
    }

    void merge(const Node& l, const Node& r) {
        v = l.v + r.v;
    }
};

/* ---------------- Update Class ---------------- */
class Update {
public:
    int v = 0;

    Update() {}
    Update(int val) {
        v = val;
    }

    void combine(const Update& other, const int& tl, const int& tr) {
        v += other.v;
    }

    void apply(Node& node, const int& tl, const int& tr) const {
        node.v += (tr - tl + 1) * v;
    }
};

/* ---------------- Segment Tree Class ---------------- */
template <typename node, typename update>
class SegTree {
public:
    int len;
    vector<node> t;
    vector<update> unpropUpd;
    vector<bool> isLazy;
    node identityElement;
    update identityTransformation;

    SegTree() {}
    SegTree(int n) {
        len = n;
        t.resize(4 * n);
        unpropUpd.resize(4 * n);
        isLazy.resize(4 * n, false);
        identityElement = node();
        identityTransformation = update();
    }

    void apply(int v, int tl, int tr, const update& upd) {
        if (tl != tr) {
            isLazy[v] = true;
            unpropUpd[v].combine(upd, tl, tr);
        }
        upd.apply(t[v], tl, tr);
    }

    void pushDown(int v, int tl, int tr) {
        if (!isLazy[v]) return;
        isLazy[v] = false;

        int tm = (tl + tr) / 2;
        apply(2 * v, tl, tm, unpropUpd[v]);
        apply(2 * v + 1, tm + 1, tr, unpropUpd[v]);
        unpropUpd[v] = identityTransformation;
    }

    template<typename T>
    void build(const T& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, 2 * v, tl, tm);
        build(a, 2 * v + 1, tm + 1, tr);
        t[v].merge(t[2 * v], t[2 * v + 1]);
    }

    node query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) return identityElement;
        if (l <= tl && tr <= r) return t[v];

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        node leftAns = query(2 * v, tl, tm, l, r);
        node rightAns = query(2 * v + 1, tm + 1, tr, l, r);
        node ans;
        ans.merge(leftAns, rightAns);
        return ans;
    }

    void rangeUpdate(int v, int tl, int tr, int l, int r, const update& upd) {
        if (tl > r || tr < l) return;
        if (l <= tl && tr <= r) {
            apply(v, tl, tr, upd);
            return;
        }

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        rangeUpdate(2 * v, tl, tm, l, r, upd);
        rangeUpdate(2 * v + 1, tm + 1, tr, l, r, upd);
        t[v].merge(t[2 * v], t[2 * v + 1]);
    }

    // Overloaded Public Interfaces
    template<typename T>
    void build(const T& a) {
        build(a, 1, 0, len - 1);
    }

    node query(int l, int r) {
        return query(1, 0, len - 1, l, r);
    }

    void rangeUpdate(int l, int r, const update& upd) {
        rangeUpdate(1, 0, len - 1, l, r, upd);
    }
};

/* ---------------- Main Driver Code ---------------- */
int main() {
    int n = 8;
    vector<int> a = {1, 2, 1, 4, 2, 3, 1, 1};

    SegTree<Node, Update> segTree(n);
    segTree.build(a);

    // Initial tree data
    cout << "Initial values:\n";
    for (int i = 0; i < n; i++)
        cout << segTree.query(i, i).v << " ";
    cout << "\n";

    // Range query
    cout << "Sum for range [1, 5]: " << segTree.query(1, 5).v << "\n";

    // Point update
    segTree.rangeUpdate(2, 2, 10);
    cout << "After setting index 2 to +10:\n";
    for (int i = 0; i < n; i++)
        cout << segTree.query(i, i).v << " ";
    cout << "\n";

    // Range updates
    segTree.rangeUpdate(2, 7, 10);
    segTree.rangeUpdate(2, 7, 20);
    cout << "After adding +10 and then +20 from index 2 to 7:\n";
    for (int i = 0; i < n; i++)
        cout << segTree.query(i, i).v << " ";
    cout << "\n";

    // Final query
    cout << "Sum for range [2, 3]: " << segTree.query(2, 3).v << "\n";

    return 0;
}












// *************************** Example usage ****************************
/*
Here’s a simple example using the provided Segment Tree with Lazy Propagation template to:

Build the tree from an integer array,

Perform range updates (adding a value to all elements in a range),

Query the sum over a range.
*/

#include <bits/stdc++.h>
using namespace std;

/* -------- Node Class -------- */
class Node {
public:
    int v = 0;
    Node() {}
    Node(int val) : v(val) {}

    void merge(const Node& l, const Node& r) {
        v = l.v + r.v;  // sum of left and right
    }
};

/* -------- Update Class -------- */
class Update {
public:
    int v = 0;
    Update() {}
    Update(int val) : v(val) {}

    void combine(const Update& other, const int& tl, const int& tr) {
        v += other.v;  // accumulate increments
    }

    void apply(Node& node, const int& tl, const int& tr) const {
        node.v += (tr - tl + 1) * v;  // add v * segment length
    }
};

/* -------- Segment Tree Template -------- */
template <typename node, typename update>
class SegTree {
public:
    int len;
    vector<node> t;
    vector<update> unpropUpd;
    vector<bool> isLazy;
    node identityElement;
    update identityTransformation;

    SegTree() {}
    SegTree(int n) {
        len = n;
        t.resize(4 * n);
        unpropUpd.resize(4 * n);
        isLazy.resize(4 * n, false);
        identityElement = node();
        identityTransformation = update();
    }

    void apply(int v, int tl, int tr, const update& upd) {
        if (tl != tr) {
            isLazy[v] = true;
            unpropUpd[v].combine(upd, tl, tr);
        }
        upd.apply(t[v], tl, tr);
    }

    void pushDown(int v, int tl, int tr) {
        if (!isLazy[v]) return;
        isLazy[v] = false;
        int tm = (tl + tr) / 2;
        apply(2 * v, tl, tm, unpropUpd[v]);
        apply(2 * v + 1, tm + 1, tr, unpropUpd[v]);
        unpropUpd[v] = identityTransformation;
    }

    template<typename T>
    void build(const T& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, 2 * v, tl, tm);
        build(a, 2 * v + 1, tm + 1, tr);
        t[v].merge(t[2 * v], t[2 * v + 1]);
    }

    node query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) return identityElement;
        if (l <= tl && tr <= r) return t[v];

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        node leftAns = query(2 * v, tl, tm, l, r);
        node rightAns = query(2 * v + 1, tm + 1, tr, l, r);
        node ans;
        ans.merge(leftAns, rightAns);
        return ans;
    }

    void rangeUpdate(int v, int tl, int tr, int l, int r, const update& upd) {
        if (tl > r || tr < l) return;
        if (l <= tl && tr <= r) {
            apply(v, tl, tr, upd);
            return;
        }

        pushDown(v, tl, tr);
        int tm = (tl + tr) / 2;
        rangeUpdate(2 * v, tl, tm, l, r, upd);
        rangeUpdate(2 * v + 1, tm + 1, tr, l, r, upd);
        t[v].merge(t[2 * v], t[2 * v + 1]);
    }

    // Public interface
    template<typename T>
    void build(const T& a) {
        build(a, 1, 0, len - 1);
    }

    node query(int l, int r) {
        return query(1, 0, len - 1, l, r);
    }

    void rangeUpdate(int l, int r, const update& upd) {
        rangeUpdate(1, 0, len - 1, l, r, upd);
    }
};

/* -------- Main Function (Example Usage) -------- */
int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = (int)arr.size();

    SegTree<Node, Update> segTree(n);
    segTree.build(arr);

    // Query sum from index 1 to 3
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3).v << "\n"; // Expect 2+3+4=9

    // Add 10 to range [2, 4]
    segTree.rangeUpdate(2, 4, Update(10));

    // Query sum again after update
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3).v << "\n"; 
    // Expect 2 + (3+10) + (4+10) = 2 + 13 + 14 = 29

    // Query sum for entire array
    cout << "Sum of entire array: " << segTree.query(0, n - 1).v << "\n";
    // Expect (1) + (2) + (3+10) + (4+10) + (5+10) = 1 + 2 + 13 + 14 + 15 = 45

    return 0;
}

