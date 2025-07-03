/*
===================== General Time Complexity Formula =====================
    Time Complexity of Recursive Code:
        O((branching_factor ^ recursion_depth) * cost_per_call)

    Where:
    - branching_factor: number of recursive calls made at each level
    - recursion_depth: maximum depth of the recursion (how deep the call stack goes)
    - cost_per_call: the amount of work done in a single recursive call

    This gives a worst-case upper bound of the total work done.

    Example:
        For generating all strings of length ≤ k using lowercase letters:
            branching_factor = 26
            recursion_depth = k
            cost_per_call = O(k) (for string operations)

        => TC = O(26^k * k)
=======================================================================
*/


/*
======================== Problem Constraints Notes ========================

Given:
    n == s.length
    2 <= k <= 2000
    2 <= n < min(2001, k * 8)
    s consists of lowercase English letters

Implications:
    - maxLen = floor(n / k)
    - Since n < k * 8, we have: maxLen < 8
    - Therefore, max possible sequence length to search is ≤ 7

Why this matters:
    - Even though brute-force recursion has a worst-case TC of O(26^maxLen * maxLen),
      it is acceptable here because:
        - maxLen is small (≤ 7) i.e 26^7 <10^9
        - character frequency pruning reduces branching factor << 26
        - early return stops deep exploration
        - lexicographically largest is searched first, giving early answer

Takeaway:
    The constraints are carefully designed to allow recursion/backtracking
    without TLE, even with exponential complexity in theory.

===========================================================================
*/


// **************************************** My Solution [Method 1] ****************************************
class Solution {
    public:
    string ans = "";

    // TC : O(n)
    bool isSubsequence(string &seq, string &s, int k) {
        int n=seq.size();

        int i = 0, j = 0;
        while (i < s.size()) {
            if (s[i] == seq[j%n]) j++;
            i++;
        }
        return j >= n*k;
    }

    // TC: O(26^maxLen * maxLen)
    void solveRec(string &seq, int maxLen, vector<int> &freq, int k, string &s) {
        if(seq.length() > maxLen) return;
        if (seq.size()!=0 && isSubsequence(seq, s, k)) {
            if(ans.size() < seq.size() || ans<seq) ans = seq;
        }

        for (int i = 25; i >= 0; --i) {
            if (freq[i] > 0) {
                seq.push_back('a' + i);
                freq[i]--;
                solveRec(seq, maxLen, freq, k, s);
                seq.pop_back();
                freq[i]++;
            }
        }
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> originalFreq(26, 0);
        for (char ch : s) originalFreq[ch - 'a']++;

        int maxLen = s.size() / k;

        // Try all possible lengths from maxLen down to 1
        vector<int> freq(26);
        for (int i = 0; i < 26; ++i) freq[i] = originalFreq[i] / k;

        string seq;
        solveRec(seq, maxLen, freq, k, s);
  
        return ans;
    }
};
// **************************************** My Solution [Method 1] ****************************************




// ****************************** My Solution [Method 2] - Optimized method 1 ******************************
/*
class Solution {
    public:
    string ans = "";

    // TC : O(n)
    bool isSubsequence(string &seq, string &s, int k) {
        string target = "";
        for (int i = 0; i < k; ++i) target += seq;

        int i = 0, j = 0;
        while (i < s.size() && j < target.size()) {
            if (s[i] == target[j]) j++;
            i++;
        }
        return j == target.size();
    }

    // TC: O(26^maxLen * maxLen)
    bool solveRec(string &seq, int maxLen, vector<int> &freq, int k, string &s) {
        if (seq.length() == maxLen) {
            if (isSubsequence(seq, s, k)) {
                ans = seq;
                return true;
            }
            return false;
        }

        for (int i = 25; i >= 0; --i) {
            if (freq[i] > 0) {
                seq.push_back('a' + i);
                freq[i]--;
                if (solveRec(seq, maxLen, freq, k, s)) return true;
                seq.pop_back();
                freq[i]++;
            }
        }
        return false;
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> originalFreq(26, 0);
        for (char ch : s) originalFreq[ch - 'a']++;

        int maxLen = s.size() / k;

        // Try all possible lengths from maxLen down to 1
        for (int len = maxLen; len >= 1; --len) {
            // Prepare fresh freq vector for this length
            vector<int> freq(26);
            for (int i = 0; i < 26; ++i)
                freq[i] = originalFreq[i] / k;

            string seq;
            if (solveRec(seq, len, freq, k, s))
                break; // Found the longest, lexicographically largest valid sequence
        }

        return ans;
    }
};
*/
// ****************************** My Solution [Method 2] - Optimized method 1 ******************************