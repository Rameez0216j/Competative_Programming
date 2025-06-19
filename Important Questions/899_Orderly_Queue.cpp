// Solution : https://www.youtube.com/watch?v=5TNRCLbU7H4
// ***************************************** My Solution *****************************************
class Solution {
    public:
    string orderlyQueue(string s, int k) {
        int n = s.size();  // Get the length of the string
        
        // Case 1: When k == 1, we can only rotate the string
        // So we try all possible rotations and return the lex smallest one
        if (k == 1) {
            string ans = s;  // Initialize answer with original string
            
            // Try all rotations by moving first i characters to the end
            for (int i = 1; i < s.size(); i++) {
                // Rotate string: substring from i to end + substring from start to i
                string temp = s.substr(i, n) + s.substr(0, i);
                
                // Update answer if the new rotation is lexicographically smaller
                if (ans > temp) ans = temp;
            }
            return ans;  // Return the smallest rotation found
        }
        
        // Case 2: When k > 1, we can obtain any permutation of the string
        // So the smallest possible string is just the sorted version
        sort(s.begin(), s.end());
        return s;
    }
};
// ***************************************** My Solution *****************************************