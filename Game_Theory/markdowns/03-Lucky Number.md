
### **Understanding the Game Rules**
1. We have an **array `A` of size `n`**.
2. Two players **Alice** and **Bob** take turns.
3. We are given two numbers **`a` and `b`**.
4. We count:
   - `cnt1` → Numbers **divisible by both `a` and `b`**.
   - `cnt2` → Numbers **divisible only by `a`**.
   - `cnt3` → Numbers **divisible only by `b`**.
5. **Who wins?**
   - If there is **at least one** number divisible by both `a` and `b`, Bob gets an extra turn (`cnt2++`).
   - If `cnt2 > cnt3`, **Bob wins**.
   - Otherwise, **Alice wins**.

---

### **Breaking Down the Code**
```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to determine the winner of the Lucky Number game
string solve(int n, int a, int b, vector<int> A) {
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;

    // Counting numbers based on divisibility
    for (int i = 0; i < n; i++) {
        if (A[i] % a == 0 && A[i] % b == 0) {
            cnt1++; // Numbers divisible by both 'a' and 'b'
        } else if (A[i] % a == 0) {
            cnt2++; // Numbers divisible only by 'a'
        } else if (A[i] % b == 0) {
            cnt3++; // Numbers divisible only by 'b'
        }
    }

    // If there is at least one number divisible by both 'a' and 'b', Bob gets an extra turn
    if (cnt1) {
        cnt2++;
    }

    // Comparing counts to determine the winner
    return (cnt2 > cnt3) ? "Bob" : "Alice";
}
```

---

### **Example Walkthrough**
#### **Example 1**
```cpp
int main() {
    vector<int> A = {10, 20, 30, 40, 50};
    int n = A.size();
    int a = 2, b = 5;
    cout << solve(n, a, b, A) << endl;
    return 0;
}
```
**Explanation**  
- `10, 20, 30, 40, 50` → All divisible by **both 2 and 5** (so `cnt1 = 5`).
- Bob gets an extra turn → `cnt2++` (Now `cnt2 = 1`).
- Since `cnt2 <= cnt3`, **Alice wins**.

```
Output: Alice
```

---

### **Key Takeaways**
1. **Count how many numbers are divisible by `a`, `b`, or both.**  
2. **If at least one number is divisible by both `a` and `b`, Bob gets an extra turn.**  
3. **Compare `cnt2` (Bob's count) and `cnt3` (Alice's count) to decide the winner.**  
4. **Time Complexity: `O(n)`, as we iterate once through the array.**  

Now, the logic should be crystal clear! 🚀
