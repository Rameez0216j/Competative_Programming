/*
===============================================================
Problem Statement:
---------------------------------------------------------------
We are given:
1. A sequence (array of integers).
2. A permutation of indices (where each index i is mapped to perm[i]).
3. A number k (how many times we apply the permutation).

We need to compute the final sequence after applying the given permutation k times.

---------------------------------------------------------------
Two Approaches:
1. Cycle Decomposition Method (O(n)) ✅ (best for large k)
2. Binary Exponentiation Method (O(n log k)) 
   - Useful if you want to exponentiate permutations in general.

===============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ----------------- UTILITY FUNCTION -----------------
vector<int> applyPermutation(const vector<int>& sequence, const vector<int>& perm) {
    int n = sequence.size();
    vector<int> newSeq(n);
    for (int i = 0; i < n; i++) {
        newSeq[i] = sequence[perm[i]];
    }
    return newSeq;
}

// ----------------- BINARY EXPONENTIATION METHOD -----------------
vector<int> permuteBinaryExpo(vector<int> sequence, vector<int> perm, long long k) {
    while (k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, perm); // apply once if odd
        }
        perm = applyPermutation(perm, perm); // square the permutation
        k >>= 1; // divide k by 2
    }
    return sequence;
}

// ----------------- CYCLE METHOD (MORE EFFICIENT) -----------------
vector<int> permuteWithCycles(vector<int> sequence, const vector<int>& perm, long long k) {
    int n = perm.size();
    vector<int> result(n);
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> cycle;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle.push_back(curr);
                curr = perm[curr];
            }

            int L = cycle.size();
            int shift = k % L;

            for (int j = 0; j < L; j++) {
                int from = cycle[j];
                int to = cycle[(j + shift) % L];
                result[to] = sequence[from];
            }
        }
    }
    return result;
}

// ----------------- DRIVER CODE -----------------
int main() {
    vector<int> seq = {10, 20, 30, 40, 50};
    vector<int> perm = {2, 0, 1, 4, 3}; 
    long long k = 7;

    cout << "Using Binary Exponentiation (O(n log k)):\n";
    vector<int> res1 = permuteBinaryExpo(seq, perm, k);
    for (int x : res1) cout << x << " ";
    cout << "\n\n";

    cout << "Using Cycle Decomposition (O(n)):\n";
    vector<int> res2 = permuteWithCycles(seq, perm, k);
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}

/*
===============================================================
Notes:
---------------------------------------------------------------
1. Binary Exponentiation Method:
   - Repeatedly squares the permutation.
   - Time complexity: O(n log k).
   - Works for general permutation exponentiation.

2. Cycle Decomposition Method:
   - Finds permutation cycles.
   - Shifts elements by (k % cycleLength).
   - Time complexity: O(n).
   - Faster if only applying permutation to a sequence.

Comparison:
- Binary Expo is good to learn, but Cycle Method is optimal in practice.
===============================================================
*/
