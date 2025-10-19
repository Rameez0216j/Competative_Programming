#include <bits/stdc++.h>
using namespace std;

/*
    Function: multiply
    -----------------
    Computes (a * b) % m using binary multiplication to avoid overflow.

    Parameters:
    - a : first number
    - b : second number
    - m : modulo

    Returns:
    - (a * b) % m without ever computing a * b directly.
    
    How it works:
    1. Base case: If a = 0, product is 0.
    2. If a is even: a * b = 2 * ((a/2) * b)
    3. If a is odd: a * b = 2 * (((a-1)/2) * b) + b
    4. At each step, we take modulo m to avoid overflow.
*/
long long multiply(long long a, long long b, long long m) {
    if (a == 0) return 0;          // Base case
    if (a % 2 == 0) {
        // a is even
        long long half = multiply(a / 2, b, m);
        return (2 * half) % m;
    } else {
        // a is odd
        long long half = multiply((a - 1) / 2, b, m);
        return (2 * half % m + b % m) % m;
    }
}


long long mulmod(long long a, long long b, long long m) {
    long long res = 0; // result
    a = a % m;

    while (b > 0) {
        if (b % 2 == 1)       // if b is odd
            res = (res + a) % m;

        a = (2 * a) % m;      // double a
        b /= 2;               // halve b
    }

    return res;
}

int main() {
    long long a = 123456789012345;
    long long b = 98765432109876;
    long long m = 1e18 + 3; // modulo can be large

    cout << "Result: " << multiply(a, b, m) << endl;
    return 0;
}
