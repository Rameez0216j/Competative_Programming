#include <bits/stdc++.h>
using namespace std;


long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1; // base case
    return nCr(n - 1, r - 1) + nCr(n - 1, r);
}


long long nPr(int n, int r) {
    if (r > n) return 0;
    if (r == 0) return 1; // base case
    return n * nPr(n - 1, r - 1);
}

int main() {
    int n = 5, r = 2;
    cout << "nPr(" << n << "," << r << ") = " << nPr(n, r) << endl;
    cout << "nCr(" << n << "," << r << ") = " << nCr(n, r) << endl;
    return 0;
}


