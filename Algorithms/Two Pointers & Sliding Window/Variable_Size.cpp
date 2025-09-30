
/*
    Use case: Finding the longest substring with at most k distinct characters
    Time: O(n)
*/
int longestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> freq;
    int i = 0, ans = 0;
    for (int j = 0; j < s.size(); j++) {
        freq[s[j]]++;
        while (freq.size() > k) {
            if (--freq[s[i]] == 0) freq.erase(s[i]);
            i++;
        }
        ans = max(ans, j - i + 1);
    }
    return ans;
}

