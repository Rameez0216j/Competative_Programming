/*
===============================================================
Fast Exponentiation (x^n)
---------------------------------------------------------------
Given two numbers x and n, compute x^n efficiently.

Naive Method: Multiply x, n times → O(n).
Optimized Method: Binary Exponentiation → O(log n).

Key idea:
- If n is even: x^n = (x^(n/2))^2
- If n is odd:  x^n = x * (x^(n-1))

===============================================================
*/

// Iterative version
long long xpown(long long x, long long n) {
    long long result = 1;
    while (n > 0) {
        if (n & 1) {           // if n is odd
            result *= x;
        }
        x *= x;                // square the base
        n >>= 1;               // divide n by 2
    }
    return result;
}

// Recursive version (optional, same idea)
long long xpownRec(long long x, long long n) {
    if (n == 0) return 1;
    long long half = xpownRec(x, n / 2);
    if (n % 2 == 0) return half * half;
    else return x * half * half;
}
