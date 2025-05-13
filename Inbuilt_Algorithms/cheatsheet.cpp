#include <bits/stdc++.h>
using namespace std;

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;  // Invalid case
    if (r == 0 || r == n) return 1;  // Base case: nCr(n, 0) = nCr(n, n) = 1
    return nCr(n - 1, r - 1) + nCr(n - 1, r);  // Pascal's Triangle recurrence
}

int nPr(int n, int r) {
    if (r < 0 || r > n) return 0;  // Invalid case
    if (r == 0) return 1;  // Base case: nP0 = 1
    return n * nPr(n - 1, r - 1);  // Recurrence relation for nPr
}

int main() {
    
    
    return 0;
}