// **************************************** Method 1 ****************************************
class Solution {
    public:
    // Step 1: Build the LPS (Longest Prefix Suffix) array
    // Build LPS array where:
    // i → matcher (prefix length)
    // j → traversal index
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

    vector<int> search(string& pattern, string& text) {
        vector<int> ans;
        vector<int> lps = buildLPS(pattern);
        int i = 0, j = 0;
    
        while (j < text.size()) {
            if (pattern[i] == text[j]) {
                i++;
                j++;
                if (i == pattern.size()) ans.push_back(j-pattern.size());
            }else {
                if (i != 0) i = lps[i - 1]; // fallback in pattern
                else j++; // advance text
            }
        }
        
        return ans;
    }
};
// **************************************** Method 1 ****************************************








// **************************************** Method 2 ****************************************
/*
class Solution
{
    public:
    
    vector <int> search(string pat, string txt)
    {
        //code here.
        vector<int> ans;
        
        string s=pat+"#"+txt; // for pattern_matching simplicity
        vector<int> kmp_arr(s.size(),0);
        int j=0,i=1;
        while(i<s.size()){
            if(s[i]==s[j]){
                kmp_arr[i]=j+1;
                i++,j++;
            }else{
                if(j!=0) j=kmp_arr[j-1];
                else i++;
            }
        }
        
        
        for(int i=pat.size();i<s.size();i++){
            if(kmp_arr[i]==pat.size()){
                ans.push_back(i-2*pat.size()+1); // +1 because Starting Index of a string should be taken as 1.
            }
        }
        
        if(ans.size()==0) return {-1};
        return ans;
    }
     
};
*/
// **************************************** Method 2 ****************************************