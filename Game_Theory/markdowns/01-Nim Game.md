

## **Nim Game**
```cpp
#include<bits/stdc++.h>
using namespace std;

bool canWinNim(int n) {
    return (n%4!=0);
}
```

---

### **Understanding the Nim Game**
#### **Game Rules:**
1. There are **n stones** in a pile.
2. You and your opponent **take turns** picking up **1, 2, or 3 stones** from the pile.
3. The **player who takes the last stone wins**.

#### **Objective:**  
Find out if the **starting player (you)** can guarantee a win if both play optimally.

---

### **Observing the Pattern**  
Let's analyze small cases first:

| `n` (No. of stones) | Winning Player (If you start first) | Reason |
|----------------|----------------|----------------|
| 1 | **Win** | Take 1 stone and win. |
| 2 | **Win** | Take 2 stones and win. |
| 3 | **Win** | Take 3 stones and win. |
| 4 | **Lose** | No matter what you take (1, 2, or 3), opponent will always win. |
| 5 | **Win** | Take 1 stone, opponent faces 4 (losing state). |
| 6 | **Win** | Take 2 stones, opponent faces 4 (losing state). |
| 7 | **Win** | Take 3 stones, opponent faces 4 (losing state). |
| 8 | **Lose** | No matter what you take (1, 2, or 3), opponent will always win. |

#### **Pattern Observed**
- If `n` is **a multiple of 4** (`n % 4 == 0`), you **always lose** if the opponent plays optimally.
- Otherwise, you **can force a win**.

---

### **Breaking Down the Code**
```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to determine if the starting player can win
bool canWinNim(int n) {
    return (n % 4 != 0); // If n is not a multiple of 4, you can win
}
```

#### **Why is this correct?**
- If `n % 4 == 0`, you will always lose (opponent can force you into a losing position).
- Otherwise, you **can take 1, 2, or 3 stones** to make the opponent face a losing scenario.

---

### **Example Walkthrough**
```cpp
int main() {
    int n;
    cout << "Enter number of stones: ";
    cin >> n;

    if (canWinNim(n))
        cout << "You can win the game!" << endl;
    else
        cout << "You will lose if opponent plays optimally." << endl;

    return 0;
}
```

#### **Example Runs**
```
Input: 6
Output: You can win the game!
```
```
Input: 8
Output: You will lose if opponent plays optimally.
```

---

### **Key Takeaways**
1. **Only multiples of 4 are losing positions**.
2. **If `n % 4 != 0`, always a winning strategy exists**.
3. **Simple modulus check solves the problem in O(1) time**.

Now you can instantly determine the winner **just by looking at `n % 4`**! 🚀🔥
