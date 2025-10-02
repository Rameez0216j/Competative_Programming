// Solution : https://www.youtube.com/watch?v=Vn2eno9OIpc
// ********************************** My Solution **********************************
class Solution {
public:
    // Check if a word can be formed using the available letter frequencies
    bool canFormWord(vector<int> &wordFreq, unordered_map<char,int> &availableLetters) {
        for (int i = 0; i < 26; i++) {
            char ch = 'a' + i;
            if (wordFreq[i] > availableLetters[ch]) return false;
        }
        return true;
    }

    // Backtracking recursive function
    int backtrackMaxScore(int index, vector<vector<int>> &wordsFreq,
                          vector<int> &letterScores, unordered_map<char,int> &availableLetters) {
        if (index == wordsFreq.size()) return 0;

        // Option 1: Include current word (if possible)
        int includeScore = 0;
        if (canFormWord(wordsFreq[index], availableLetters)) {
            int currentWordScore = 0;

            // Deduct used letters and calculate word's score
            for (int i = 0; i < 26; i++) {
                char ch = 'a' + i;
                availableLetters[ch] -= wordsFreq[index][i];
                currentWordScore += wordsFreq[index][i] * letterScores[i];
            }

            includeScore = currentWordScore + backtrackMaxScore(index + 1, wordsFreq, letterScores, availableLetters);

            // Backtrack: restore letters
            for (int i = 0; i < 26; i++) {
                char ch = 'a' + i;
                availableLetters[ch] += wordsFreq[index][i];
            }
        }

        // Option 2: Exclude current word
        int excludeScore = backtrackMaxScore(index + 1, wordsFreq, letterScores, availableLetters);

        // Return the maximum of both choices
        return max(includeScore, excludeScore);
    }

    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& letterScores) {
        // Precompute frequency vector for each word
        vector<vector<int>> wordsFreq;
        for (string &word : words) {
            vector<int> freq(26, 0);
            for (char &ch : word) freq[ch - 'a']++;
            wordsFreq.push_back(freq);
        }

        // Frequency map of available letters
        unordered_map<char,int> availableLetters;
        for (char ch : letters) availableLetters[ch]++;

        return backtrackMaxScore(0, wordsFreq, letterScores, availableLetters);
    }
};
// ********************************** My Solution **********************************