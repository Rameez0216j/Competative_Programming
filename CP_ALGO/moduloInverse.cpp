// Video : https://www.youtube.com/watch?v=FMBW7m1Wap0&t=416s
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9+7;

// Fast modular exponentiation (Binary exponentiation x^y with mod p)
long long modPow(long long x, long long y, long long p) {
    long long res = 1;
    x %= p;
    while (y > 0) {
        if (y % 2 == 1) res = (res * x) % p;
        y /= 2;
        x = (x * x) % p;
    }
    return res;
}

// Precompute factorials modulo MOD
vector<long long> fact;

void computeFactorials(int n) {
    fact.resize(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (fact[i-1] * i) % MOD;
}

// Compute nCr modulo MOD using modular inverse
long long nCr_mod(int n, int r) {
    if (r > n) return 0;
    long long numerator = fact[n];
    long long denominator = (fact[r] * fact[n-r]) % MOD;
    long long inverseDenom = modPow(denominator, MOD-2, MOD); // Fermat's little theorem ==> a^(M-2) mod M = (a^-1) mod M if a and M are coPrimes
    return (numerator * inverseDenom) % MOD;
}

int main() {
    int n = 5, r = 2;
    computeFactorials(n);
    cout << "nCr(" << n << "," << r << ") % " << MOD << " = " << nCr_mod(n,r) << endl;
    return 0;
}
