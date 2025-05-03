### **Understanding the Game Rules**  
1. The game starts with an integer `n`.
2. Two players **Alice** and **Bob** take turns.
3. **Alice starts first**.
4. On each turn, the current player **must pick a divisor of `n` (x) such that 1 ≤ x < n** and subtract it from `n` (i.e., `n = n - x`).
5. The **player who cannot make a move loses**.

---

### **Observing Small Cases**
Let's analyze some small values of `n` to find a pattern:

| `n`  | Winner  | Reason  |
|------|--------|---------|
| 1    | ❌ **Bob Wins**  | Alice has no valid moves. She loses instantly. |
| 2    | ✅ **Alice Wins** | Alice can subtract 1, leaving `n = 1`. Bob has no move left. |
| 3    | ❌ **Bob Wins**  | Alice can only subtract 1 (leaving `n = 2`), but now Bob is in a winning position. |
| 4    | ✅ **Alice Wins** | Alice subtracts 1, leaving `n = 3`, putting Bob in a losing position. |
| 5    | ❌ **Bob Wins**  | Alice can only subtract 1 (leaving `n = 4`), but Bob is now in a winning position. |
| 6    | ✅ **Alice Wins** | Alice subtracts 1 (leaving `n = 5`), putting Bob in a losing position. |

---

### **Observing the Pattern**
- **If `n` is Even (`n % 2 == 0`)** → **Alice Wins** ✅
- **If `n` is Odd (`n % 2 != 0`)** → **Bob Wins** ❌  

#### **Why Does This Work?**
- If `n` is **even**, Alice can always subtract 1 and give Bob an **odd** number.
- If `n` is **odd**, Alice is forced to give Bob an **even** number, which he can always manipulate back to an odd one.
- Eventually, Bob will always win when `n` is odd.

Thus, the entire game **boils down to checking if `n` is even or odd**.

---

### **Breaking Down the Code**
```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to determine if Alice can win
bool divisorGame(int n) {
    return (n % 2 == 0); // Alice wins if 'n' is even
}
```

#### **Why is this correct?**
- If `n` is **even**, Alice **always wins** by subtracting 1 and forcing Bob into an odd position.
- If `n` is **odd**, Bob **always wins** because Alice is forced into an even position.

---

### **Example Walkthrough**
```cpp
int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (divisorGame(n))
        cout << "Alice can win!" << endl;
    else
        cout << "Bob will win!" << endl;

    return 0;
}
```

#### **Example Runs**
```
Input: 6
Output: Alice can win!
```
```
Input: 7
Output: Bob will win!
```

---

### **Key Takeaways**
1. **If `n` is even → Alice wins** ✅  
2. **If `n` is odd → Bob wins** ❌  
3. **Game boils down to checking if `n` is even or odd in O(1) time** 🚀  

Now you can instantly determine the winner **just by looking at `n % 2`**! 🎯
