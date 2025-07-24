// Classic KMP Algorithm Approach
// ************************************ My Solution ************************************
class Solution {
    public:
    vector<int> buildLPS(string pattern) {
        int n = pattern.size();
        vector<int> lps(n, 0);
    
        int i = 0; // length of the current longest prefix suffix
        for (int j = 1; j < n; ) {
            if (pattern[i] == pattern[j]) {
                lps[j] = i+1;
                i++;
                j++;
            } else {
                if (i != 0) i = lps[i - 1]; // fallback
                else j++;
            }
        }
    
        return lps;
    }

    string longestPrefix(string s) {
        vector<int> LPS=buildLPS(s);
        int len=LPS.back();
        string ans=s.substr(0,len);
        return ans;
    }
};
// ************************************ My Solution ************************************