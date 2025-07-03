// EXACT SUBPROBLEM OF [1931 Painting a Grid With Three Different Colors] - just place 3 in place on m
// Solution : https://www.youtube.com/watch?v=Qz8F-nC8oxQ&t=1956s
// ********************************************* My Solution *********************************************
class Solution {
    vector<string> columnPatterns;
    const int MOD = 1e9 + 7;

    public:
    // Generate all valid column patterns (no two adjacent cells have same color)
    void generateColumnPatterns(string &current, int m) {
        if (current.size() == m) {
            columnPatterns.push_back(current);
            return;
        }

        for (char color : {'R', 'G', 'B'}) {
            if (!current.empty() && current.back() == color) continue;
            current.push_back(color);
            generateColumnPatterns(current, m);
            current.pop_back();
        }
    }

    // Check if two columns are compatible (no same color in same row)
    bool isCompatible(const string &a, const string &b) {
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] == b[i]) return false;
        }
        return true;
    }

    // Recursion
    int countWaysRec(int colIndex, int prevPatternIndex, int totalCols) {
        if (colIndex == totalCols) return 1;

        int totalWays = 0;
        for (int i = 0; i < columnPatterns.size(); ++i) {
            if (prevPatternIndex == -1 || isCompatible(columnPatterns[prevPatternIndex], columnPatterns[i])) {
                totalWays = (totalWays + countWaysRec(colIndex + 1, i, totalCols)) % MOD;
            }
        }

        return totalWays;
    }

    // Recursion with memoization
    int countWaysRec_Mem(int colIndex, int prevPatternIndex, int totalCols, vector<vector<int>> &dp) {
        if (colIndex == totalCols) return 1;

        if (dp[colIndex][prevPatternIndex + 1] != -1)
            return dp[colIndex][prevPatternIndex + 1];

        int totalWays = 0;

        for (int i = 0; i < columnPatterns.size(); ++i) {
            if (prevPatternIndex == -1 || isCompatible(columnPatterns[prevPatternIndex], columnPatterns[i])) {
                totalWays = (totalWays + countWaysRec_Mem(colIndex + 1, i, totalCols, dp)) % MOD;
            }
        }

        return dp[colIndex][prevPatternIndex + 1] = totalWays;
    }

    int numOfWays(int n){
        // Recursion
        // string currentPattern = "";
        // generateColumnPatterns(currentPattern, 3);
        // return countWaysRec(0, -1, n);




        // Recursion + Memoization
        string currentPattern = "";
        generateColumnPatterns(currentPattern, 3);

        int patternCount = columnPatterns.size();
        vector<vector<int>> dp(n + 1, vector<int>(patternCount + 1, -1));

        return countWaysRec_Mem(0, -1, n, dp);
    }
};
// ********************************************* My Solution *********************************************
