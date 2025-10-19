/*
Rabin-Karp Algorithm for Pattern Matching

Problem:
- Given a text T and pattern P, find all occurrences of P in T.

Key Idea:
1. Compute a **hash of the pattern**.
2. Compute **rolling hash of every substring of T** with the same length as P.
3. Compare hashes:
   - If hashes match, check actual substring (to avoid collision).
4. Rolling hash allows updating hash in O(1) when moving window.

Time Complexity:
- Average: O(n + m) where n = text length, m = pattern length
- Worst: O(n*m) (rare, due to hash collisions)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;  // large prime
const ll BASE = 31;      // base for polynomial rolling hash

// Function to compute hash of a string
ll computeHash(const string &s) {
    ll hashValue = 0, p = 1;
    for (char c : s) {
        hashValue = (hashValue + (c - 'a' + 1) * p) % MOD;
        p = (p * BASE) % MOD;
    }
    return hashValue;
}

// Rabin-Karp search
vector<int> rabinKarp(const string &text, const string &pattern) {
    int n = text.size(), m = pattern.size();
    vector<int> occurrences;
    if (m > n) return occurrences;

    ll patternHash = computeHash(pattern);
    ll currentHash = 0, power = 1;

    // Compute hash of first window in text
    for (int i = 0; i < m; i++) {
        currentHash = (currentHash + (text[i] - 'a' + 1) * power) % MOD;
        if (i < m - 1) power = (power * BASE) % MOD; // BASE^(m-1)
    }

    // Check first window
    if (currentHash == patternHash && text.substr(0, m) == pattern) {
        occurrences.push_back(0);
    }

    // Rolling hash for remaining windows
    for (int i = 1; i <= n - m; i++) {
        // Remove first character and add next character
        currentHash = (currentHash - (text[i - 1] - 'a' + 1) + MOD) % MOD; // remove old char
        currentHash = (currentHash * BASE) % MOD;                           // shift left
        currentHash = (currentHash + (text[i + m - 1] - 'a' + 1) * 1) % MOD; // add new char

        // If hashes match, check actual substring to avoid collision
        if (currentHash == patternHash && text.substr(i, m) == pattern) {
            occurrences.push_back(i);
        }
    }

    return occurrences;
}

int main() {
    string text = "ababcababc";
    string pattern = "abc";

    vector<int> res = rabinKarp(text, pattern);
    for (int idx : res) {
        cout << "Pattern found at index " << idx << "\n";
    }
}
