#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
    vector<int> bit;  // Binary Indexed Tree
    int n;

    public:
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);  // 1-based indexing
    }

    // Adds value 'val' at index 'i'
    void update(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += (i & -i);  // Go to next
        }
    }

    // Returns prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= (i & -i);  // Go to parent
        }
        return sum;
    }

    // Returns sum from l to r (inclusive)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    vector<int> arr = {0, 1, 7, 3, 0, 7, 8, 3};  // 1-based array; 0 at index 0 is dummy
    int n = arr.size() - 1;

    FenwickTree ft(n);
    for (int i = 1; i <= n; ++i) {
        ft.update(i, arr[i]);
    }

    cout << "Sum of first 5 elements: " << ft.query(5) << endl;           // 1+7+3+0+7 = 18
    cout << "Sum from index 3 to 6: " << ft.rangeQuery(3, 6) << endl;     // 3+0+7+8 = 18

    ft.update(3, 5);  // Add 5 at index 3
    cout << "New sum from index 3 to 6: " << ft.rangeQuery(3, 6) << endl; // Now includes 3+5 = 8

    return 0;
}
