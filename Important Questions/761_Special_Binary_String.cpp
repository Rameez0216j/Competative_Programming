// ************************************ My Solution ************************************
class Solution {
    public:
    string solveRec(string s){
        vector<string> temp;

        int i=0;
        int j=0;
        int count=0;
        int n=s.size();

        for(j=0;j<n;j++){
            if(s[j]=='0') count--;
            else count++;
            
            // We found an internal special binary string 
            // Give string is always a binary string and as per question
            // "Every prefix of the binary string has at least as many 1's as 0's." so always it will start with 1 and en with 0 
            // so ==> "1"+solveRec(s.substr(i+1,j-i))+"0";
            if(count==0){
                temp.push_back("1"+solveRec(s.substr(i+1,j-i))+"0");
                i=j+1;
                // j=j+1;  already for loop does this 
            }
        }

        sort(temp.begin(),temp.end(),[](const string &a,const string &b){
            return a>b;
        });

        string ans="";
        for(string s:temp) ans+=s;
        return ans;
    }

    string makeLargestSpecial(string s) {
        return solveRec(s);
    }
};
// ************************************ My Solution ************************************






// ************************************ My Solution [with Explaination] ************************************
/*
class Solution {
public:
    // Recursively decomposes the string into special binary substrings,
    // sorts them in descending order, and combines to form the largest special string.
    string solveRec(string s) {
        vector<string> temp;  // To store valid special substrings after recursive transformation.

        int i = 0;            // Start index of a potential special substring.
        int count = 0;        // Balancing count to find special substrings.
        int n = s.size();

        // Traverse the input string to find balanced special substrings.
        for (int j = 0; j < n; j++) {
            // Increase/decrease count to track balance between '1' and '0'.
            if (s[j] == '1') count++;
            else count--;

            // A count of zero indicates a valid special binary substring from i to j.
            if (count == 0) {
                // Recursively process the inner part (excluding outer '1' and '0'),
                // and wrap it again with '1' and '0' to maintain structure.
                temp.push_back("1" + solveRec(s.substr(i + 1, j - i - 1)) + "0");

                // Move the starting point to the next position after j
                i = j + 1;

                // Don't increment j manually; the for loop already does it.
            }
        }

        // Sort the collected special substrings in descending lexicographical order
        // to ensure the largest possible combined string (greedy strategy).
        sort(temp.begin(), temp.end(), [](const string &a, const string &b) {
            return a > b;  // Descending order
        });

        // Concatenate all sorted special substrings to build the final answer.
        string ans = "";
        for (const string &s : temp) ans += s;

        return ans;
    }

    // Main function called by Leetcode to start the recursion.
    string makeLargestSpecial(string s) {
        return solveRec(s);
    }
};
*/
// ************************************ My Solution [with Explaination] ************************************