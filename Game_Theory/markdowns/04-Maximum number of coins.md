# Maximum Coins (3n Piles of Coins)

## Problem Description

There are **3n piles of coins** of varying size, and you and your friends will take piles of coins as follows:

1. In each step, you will choose any 3 piles of coins (not necessarily consecutive).
2. Of your choice:
   - **Alice** will pick the pile with the maximum number of coins.
   - **You** will pick the next pile with the maximum number of coins.
   - **Bob** will pick the last pile.

Repeat until there are no more piles of coins.

**Objective:**  
Return the maximum number of coins that **you** can have.

### Example 1:
**Input:**  
`piles = [2, 4, 1, 2, 7, 8]`

**Output:**  
`9`

**Explanation:**  
Choose the triplet `(2, 7, 8)`:
- Alice picks 8, you pick 7, and Bob picks 2.

Choose the triplet `(1, 2, 4)`:
- Alice picks 4, you pick 2, and Bob picks 1.

The maximum number of coins you can have are: `7 + 2 = 9`.

---

### Approach

1. **Sort the piles** in descending order to ensure we prioritize the larger piles.
2. **Pick the second-largest pile** from each group of three piles. Alice will pick the largest, and Bob will pick the third one.
3. The strategy is to collect the **second-largest** pile from each group of three piles to maximize your coin collection.

### Code Implementation

```cpp
#include<bits/stdc++.h>
using namespace std;

int maxCoins(vector<int>& piles) {
    // Step 1: Sort the piles in descending order
    sort(piles.begin(), piles.end(), greater<int>());
    
    int n = piles.size() / 3; // We know there are 3n piles
    int ans = 0;
    
    // Step 2: Pick the second largest pile in each triplet
    for (int i = 1; i < n * 2; i += 2) {
        ans += piles[i];  // Add the second largest pile in each triplet
    }
    
    return ans;
}

int main() {
    // Example 1
    vector<int> piles1 = {2, 4, 1, 2, 7, 8};
    cout << "Maximum coins (Example 1): " << maxCoins(piles1) << endl;

    // Example 2
    vector<int> piles2 = {2, 4, 5};
    cout << "Maximum coins (Example 2): " << maxCoins(piles2) << endl;

    // Example 3
    vector<int> piles3 = {9, 8, 7, 6, 5, 1, 2, 3, 4};
    cout << "Maximum coins (Example 3): " << maxCoins(piles3) << endl;
    
    return 0;
}
