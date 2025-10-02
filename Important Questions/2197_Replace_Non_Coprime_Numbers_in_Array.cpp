// Solution : https://www.youtube.com/watch?v=ll-m8RR7EcU
// ************************************* My Solution *************************************
/*
==============================================================
📌 STACK PATTERN FOR ADJACENT + RECURSIVE PROCESSING IN ARRAYS
==============================================================

🔑 When to Use:
- You need to process elements of an array *based on adjacency*.
- Processing may cause "recursive" merging with *previous* elements.
- Final structure must contain only valid elements (like a filtered array).

-----------------------------------
⚙️ Core Idea:
- Treat the result as a stack.
- Traverse elements one by one:
    - Push the current element tentatively.
    - If the "adjacency condition" is violated (e.g., gcd > 1, duplicate, etc.),
      merge or discard elements until the condition is satisfied.
- Continue until all elements are processed.
- The stack now holds the processed array.

-----------------------------------
📖 Template (in words, not code):
1. Initialize empty stack `result`.
2. For each element in array:
   a. Let current = element.
   b. While stack not empty AND condition(stack.top, current) holds:
        → merge current with stack.top
        → pop stack
   c. Push current into stack.
3. Return stack as final result.

-----------------------------------
✅ Example Problems (LeetCode):
- 2197 Replace Non-Coprimes → condition = gcd(a, b) > 1, merge = lcm(a, b).
- 1047 Remove Adjacent Duplicates in String → condition = chars are equal, merge = remove both.
- 71 Simplify Path → condition = ".." moves back, merge = pop last dir.
- 402 Remove K Digits → condition = stack.top > current digit, merge = pop.

-----------------------------------
⏱️ Complexity:
- Each element is pushed and popped at most once → O(n).
- Each condition check depends on problem (e.g., gcd → O(log A)).

-----------------------------------
🚀 Key Takeaway:
👉 Use this approach when adjacency processing
   may trigger cascading/recursive fixes with previous elements.
   Stack ensures correctness with minimal effort.

==============================================================
*/

class Solution
{
public:
    vector<int> replaceNonCoprimes(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> result;
        result.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            long long currentValue = nums[i]; // use long long to avoid overflow

            // Merge until the last number and currentValue are coprime
            while (!result.empty() && gcd(currentValue, result.back()) > 1)
            {
                currentValue = lcm(currentValue, result.back());
                result.pop_back();
            }

            result.push_back(currentValue);
        }

        return result;
    }
};
// ************************************* My Solution *************************************

// ************************************* Editorial *************************************
/*
class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> ans;
        for (int num : nums) {
            while (!ans.empty()) {
                int g = gcd(ans.back(), num);
                if (g > 1) {
                    num = ans.back() / g * num;
                    ans.pop_back();
                } else {
                    break;
                }
            }
            ans.push_back(num);
        }
        return ans;
    }
};
*/
// ************************************* Editorial *************************************
