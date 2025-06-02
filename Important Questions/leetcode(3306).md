# 🚀 Generalized Sliding Window Logic  

## 📌 Statement  
If you have **n conditions** in a sliding window problem:  
- You need **(n-1) while loops**, each handling an **exact condition** by shrinking the window.  
- The **last while loop** handles all **exact conditions and variable conditions together**, ensuring correctness before shrinking further.  
- The **main loop continues expanding** the window until all elements are processed.  

---

## ✅ **Generalized Sliding Window Code**  

```cpp
while (end < n) {
    
    // Shrinking for exact conditions one by one
    while (!exact_condition_1) {
        start++;  // Shrink window
    }

    while (!exact_condition_2) {
        start++;  // Shrink window
    }

    // Final while loop ensuring all conditions are met before shrinking
    while (exact_condition_1 && exact_condition_2 && variable_conditions) {
        // Process result if required
        start++;  // Shrink window further
    }

    end++;  // Expand window
}




# LeetCode Problem 3306: Count of Substrings Containing Every Vowel and K Consonants II

## Problem Statement

Given a string `word` and a non-negative integer `k`, return the total number of substrings of `word` that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly `k` consonants.

**Example 1:**

- **Input:** `word = "aeioqq"`, `k = 1`
- **Output:** `0`
- **Explanation:** There is no substring with every vowel.

**Example 2:**

- **Input:** `word = "aeiou"`, `k = 0`
- **Output:** `1`
- **Explanation:** The only substring with every vowel and zero consonants is `"aeiou"`.

**Example 3:**

- **Input:** `word = "ieaouqqieaouqq"`, `k = 1`
- **Output:** `3`
- **Explanation:** The substrings with every vowel and one consonant are:
  - `"ieaouq"`
  - `"qieaou"`
  - `"ieaouq"`

**Constraints:**

- `5 <= word.length <= 2 * 10^5`
- `word` consists only of lowercase English letters.
- `0 <= k <= word.length - 5`

## Solution

```cpp
class Solution {
private:
    // Function to check if a character is a vowel
    bool isVowel(char ch) {
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }

public:
    long long countOfSubstrings(string word, int k) {
        long long consonants = 0; // Count of consonants in the current window
        long long ans = 0; // Stores the total number of valid substrings
        int n = word.size();
        unordered_map<char, long long> vowels; // Stores the frequency of vowels in the current window

        vector<int> nextConsonant(n); // Stores the index of the next consonant for each position
        int nextConsonantIndex = n; // Default index set to size of the string (out of bounds)
        
        // Precompute the next consonant index for each position
        for (int i = n - 1; i >= 0; i--) {
            nextConsonant[i] = nextConsonantIndex;
            if (!isVowel(word[i])) {
                nextConsonantIndex = i; // Update the next consonant index
            }
        }
        
        int i = 0; // Left pointer of the sliding window
        int j = 0; // Right pointer of the sliding window
        
        while (j < n) {
            // Include the current character in the window
            if (isVowel(word[j])) vowels[word[j]]++; // Track vowel frequency
            else consonants++; // Increment consonant count

            // Ensure the window contains exactly k consonants
            while (consonants > k) {
                if (isVowel(word[i])) { 
                    vowels[word[i]]--;
                    if (vowels[word[i]] == 0) vowels.erase(word[i]); // Remove vowel if count becomes zero
                } else consonants--; // Decrease consonant count
                i++; // Shrink the window from the left
            }
            
            // Once the window has exactly k consonants, check if it contains all 5 vowels at least once
            while (j < n && vowels.size() == 5 && consonants == k) {
                // Since all characters between j and next consonant contribute to valid substrings,
                // add their contribution
                ans += (nextConsonant[j] - j);
                
                // Shrink the window and check for further valid substrings
                if (isVowel(word[i])) {
                    vowels[word[i]]--;
                    if (vowels[word[i]] == 0) vowels.erase(word[i]); // Remove vowel if its count is zero
                } else consonants--; // Reduce consonant count
                i++;
            }

            j++; // Expand the window from the right
        }

        return ans;
    }
};