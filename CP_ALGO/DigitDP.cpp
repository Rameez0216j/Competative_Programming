/*
Digit DP Template in C++
------------------------
Problem solved here: Count number of ones in all numbers from 0 to N
Can be generalized for:
- Sum of digits divisible by K
- Count numbers with certain property
- Digit masks (distinct digits)
- Palindromes
- Range [L, R] queries
*/

#include <bits/stdc++.h>
using namespace std;

class DigitDP {
public:
    // Recursive version (no memoization)
    // pos      -> current digit index (0 = most significant)
    // numStr   -> string representation of N
    // count    -> current count of ones (or any property)
    // isTight  -> true if prefix so far equals N's prefix
    int countOnesRec(int pos, string &numStr, int count, bool isTight) {
        if (pos == numStr.size()) return count; // reached end of number

        int ans = 0;
        int upperLimit = isTight ? numStr[pos] - '0' : 9;

        for (int digit = 0; digit <= upperLimit; digit++) {
            ans += countOnesRec(pos + 1, numStr, count + (digit == 1),
                                isTight && (digit == upperLimit));
        }
        return ans;
    }

    // Recursive + Memoization version
    int countOnesMemo(int pos, string &numStr, int count, bool isTight,
                      vector<vector<vector<int>>> &dp) {
        if (pos == numStr.size()) return count;

        if (dp[pos][count][isTight] != -1) return dp[pos][count][isTight];

        int ans = 0;
        int upperLimit = isTight ? numStr[pos] - '0' : 9;

        for (int digit = 0; digit <= upperLimit; digit++) {
            ans += countOnesMemo(pos + 1, numStr, count + (digit == 1),
                                 isTight && (digit == upperLimit), dp);
        }

        return dp[pos][count][isTight] = ans;
    }

    // Public function to count number of ones <= n
    int countDigitOne(int n) {
        string numStr = to_string(n);

        // Recursion only
        // return countOnesRec(0, numStr, 0, true);

        // Recursion + Memoization
        int maxDigits = numStr.size();
        vector<vector<vector<int>>> dp(maxDigits + 1,
                                       vector<vector<int>>(maxDigits + 1,
                                                           vector<int>(2, -1)));
        return countOnesMemo(0, numStr, 0, true, dp);
    }
};

int main() {
    int N;
    cin >> N;

    DigitDP solver;
    int totalOnes = solver.countDigitOne(N);

    cout << "Number of ones from 0 to " << N << " = " << totalOnes << endl;
    return 0;
}















// Sum of digits divisible by 3
#include <bits/stdc++.h>
using namespace std;

string num;
int dp[20][2][3]; // pos, tight, sum_mod3

// pos: current digit position
// tight: 1 if current prefix is equal to N's prefix
// sum_mod: current sum of digits % 3
int countDiv3(int pos, int tight, int sum_mod) {
    if (pos == num.size()) // reached end of number
        return sum_mod == 0 ? 1 : 0;

    if (dp[pos][tight][sum_mod] != -1) 
        return dp[pos][tight][sum_mod];

    int limit = tight ? (num[pos] - '0') : 9;
    int ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        int newTight = tight && (digit == limit);
        int newSumMod = (sum_mod + digit) % 3;
        ans += countDiv3(pos + 1, newTight, newSumMod);
    }

    return dp[pos][tight][sum_mod] = ans;
}

int main() {
    long long N;
    cin >> N;

    num = to_string(N);
    memset(dp, -1, sizeof(dp));

    int ans = countDiv3(0, 1, 0);
    cout << "Numbers <= " << N << " divisible by 3: " << ans << endl;
}

