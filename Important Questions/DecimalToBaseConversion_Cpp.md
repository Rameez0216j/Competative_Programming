
# Decimal to Arbitrary Base Conversion in C++

This document captures a detailed explanation and implementation of converting a string representing a decimal number into a different base, along with a deep dive into the logic behind it.

---

## 🧠 Purpose

Convert a string representing a **decimal number** to a string representing the number in a different **radix/base** (e.g., 2 for binary, 8 for octal, etc.).

---

## ✅ C++ Implementation (Without `std::`)

```cpp
#include <vector>
#include <string>
#include <iostream>

std::string convertNumToBase(const std::string &decimalStr, int base) {
    int n = decimalStr.size();
    std::vector<int> num(n);
    for (int i = 0; i < n; ++i)
        num[i] = decimalStr[i] - '0';

    std::vector<int> result;
    int len = n;

    while (len > 0) {
        int remainder = 0;
        std::vector<int> next(len);
        int newLen = 0;
        bool leadingZero = true;

        for (int i = 0; i < len; ++i) {
            long long current = remainder * 10LL + num[i];
            int quotient = current / base;
            remainder = current % base;

            if (quotient != 0 || !leadingZero) {
                next[newLen++] = quotient;
                leadingZero = false;
            }
        }

        result.push_back(remainder);
        num = next;
        len = newLen;
    }

    std::string converted;
    for (auto it = result.rbegin(); it != result.rend(); ++it)
        converted += char('0' + *it);

    return converted.empty() ? "0" : converted;
}
```

---
# Example - 1
## 🎯 Goal
We are given a decimal number **as a string**, e.g., `"1234"`, and we want to convert it to **another base** (between 2 and 10).

## 📌 Why given as a string?
Because the number can be very large — potentially larger than `int` or `long long` can handle. So we manually simulate the division (like how we do on paper) using arrays.

## ✅ Key Idea
The base conversion is done by **repeatedly dividing the number by the base**, and collecting the **remainders**. The remainders (collected in reverse order) form the final number in the target base.

## 🧠 Algorithm Steps with Explanation

### Let's say:

```cpp
string str = "1234"; // decimal number
int base = 7;        // target base
```

### 🔹 Step 1: Convert the string to a digit array

```cpp
vector<int> num;
for (char ch : str) {
    num.push_back(ch - '0');
}
// num = {1, 2, 3, 4}
```

### 🔹 Step 2: Repeated Division Simulation

We repeat these steps until the number becomes 0:
1. Divide the number by `base`
2. Store the remainder
3. The quotient becomes the new number for the next iteration

```cpp
while (len > 0) {
    int remainder = 0;
    vector<int> next;
    bool leadingZero = true;

    for (int i = 0; i < len; ++i) {
        int current = remainder * 10 + num[i];
        int quotient = current / base;
        remainder = current % base;

        if (quotient != 0 || !leadingZero) {
            next.push_back(quotient);
            leadingZero = false;
        }
    }

    baseDigits.push_back(remainder);
    num = next;
    len = num.size();
}
```

## 📚 Example: Convert `"1234"` to base `7`

We'll track:
- `num` = array of digits we are dividing
- `remainder` = becomes a digit in the base-7 number
- `next` = the quotient after dividing by base (used for the next round)

### 🔄 1st Iteration

**num = {1, 2, 3, 4}**

| Step | current     | quotient | remainder |
|------|-------------|----------|-----------|
| 1    | 1           | 0        | 1         |
| 2    | 12 (1*10+2) | 1        | 5         |
| 3    | 53 (5*10+3) | 7        | 4         |
| 4    | 44 (4*10+4) | 6        | 2         |

- Quotient: `{1, 7, 6}`
- Remainder: `2`

### 🔄 2nd Iteration

**num = {1, 7, 6}**

| Step | current     | quotient | remainder |
|------|-------------|----------|-----------|
| 1    | 1           | 0        | 1         |
| 2    | 17 (1*10+7) | 2        | 3         |
| 3    | 36 (3*10+6) | 5        | 1         |

- Quotient: `{2, 5}`
- Remainder: `1`

### 🔄 3rd Iteration

**num = {2, 5}**

| Step | current     | quotient | remainder |
|------|-------------|----------|-----------|
| 1    | 2           | 0        | 2         |
| 2    | 25          | 3        | 4         |

- Quotient: `{3}`
- Remainder: `4`

### 🔄 4th Iteration

**num = {3}**

| Step | current     | quotient | remainder |
|------|-------------|----------|-----------|
| 1    | 3           | 0        | 3         |

- Quotient: `{}`
- Remainder: `3`

### 🔚 Final Step: Reverse the base digits

Collected remainders: `{2, 1, 4, 3}`

Final base-7 representation: `{3, 4, 1, 2}` → `"3412"`

## ✅ Final Answer

```cpp
cout << convertNumToBase("1234", 7);  // Output: 3412
```

## 💡 Summary

| Step                     | What it Does                         |
|--------------------------|--------------------------------------|
| Convert string to digits | To manually simulate large division |
| Long divide by base      | Collect remainders → digits of base |
| Avoid leading zeros      | Cleaner quotient for next round     |
| Reverse remainders       | Get correct base representation     |



---
# Example - 2
## 🔍 Deep Dive into Logic

### Input

- A string `decimalStr` (e.g. `"1002"`)
- A base `b` (e.g. 7)

---

### What is Happening?

You're simulating **manual division** of a number represented by a string.

At each step:
- You divide the number by `base`.
- Store the **remainder** (this is the last digit in new base).
- The **quotient** becomes the new number for the next iteration.

You keep doing this until the quotient becomes 0.

---

### 🧠 What Does This Block Do?

```cpp
if (quotient != 0 || !leadingZero)
```

It skips **leading zeroes** in the quotient during manual division.

#### Why?
If you include leading zeroes in your quotient vector:
- You get extra zeroes in the result.
- Final base conversion is wrong.

#### Example:

Convert `"1002"` to base 7:

| Step | Current | Quotient | Remainder | Stored in Result |
|------|---------|----------|-----------|------------------|
| 0    | 1       | 0        | 1         | No (leading zero)|
| 1    | 10      | 1        | 3         | Yes              |
| 2    | 32      | 4        | 4         | Yes              |
| 3    | 42      | 6        | 0         | Yes              |

Without `leadingZero` check: `[0, 1, 4, 6]` ❌  
With it: `[1, 4, 6]` ✅

---

## ✅ Final Note

This method works for base conversions up to base 10 as it's digit-by-digit (uses char - '0').

For bases > 10 (like hexadecimal), you’d need to map digits > 9 to characters A–F.

---

Let me know if you'd like that version too!
