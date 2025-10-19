/***************************************************
 🧠 C++ MACROS — NOTES & EXAMPLES
****************************************************/

/*
👉 1. What is a Macro?
   - A macro is a preprocessor directive that tells the compiler to
     replace certain code before actual compilation.
   - Defined using `#define`.
   - Processed by the *preprocessor*, not the compiler.
*/

// Example:
#define PI 3.14159

/*
When you write:
   double area = PI * r * r;
The preprocessor replaces it with:
   double area = 3.14159 * r * r;
*/

/***************************************************
 🧩 2. TYPES OF MACROS
****************************************************/

/*--------------------------------------------------
(a) Object-like Macros  ➜ act like constants
--------------------------------------------------*/
#define MAX_SIZE 100
#define DEBUG_MODE true

/*--------------------------------------------------
(b) Function-like Macros ➜ act like inline functions
--------------------------------------------------*/
#define SQUARE(x) ((x) * (x))   // Parentheses are important!
#define ADD(a,b)  ((a) + (b))

/*
   Example:
   int val = SQUARE(5 + 1);  // Expands to ((5 + 1) * (5 + 1)) = 36
   Without parentheses it would become (5 + 1 * 5 + 1) = 11 ❌
*/

/***************************************************
 ⚙️ 3. USEFUL UTILITY MACROS
****************************************************/

// Shorten code for commonly used operations
#define all(container) (container).begin(), (container).end()
#define sz(container)  ((int)(container).size())
#define pb push_back
#define ff first
#define ss second

/*
Usage:
   sort(all(vec));        // expands to sort(vec.begin(), vec.end());
   cout << sz(vec);       // prints vec.size()
*/

/***************************************************
 ⚠️ 4. COMMON MISTAKES & PITFALLS
****************************************************/

/*
❌ Missing parentheses:
   #define SQUARE(x) x*x
   SQUARE(1+2) ➜ expands to 1+2*1+2 = 5, not 9

✅ Fix: wrap everything
   #define SQUARE(x) ((x)*(x))
*/

/*
❌ Trailing semicolon:
   #define PRINT(x) cout << x << endl;
   if (cond)
       PRINT("Hi");
   else
       cout << "No";     // ➜ "else" will break because of ';'

✅ Fix: Use do-while(0) trick for safety:
   #define PRINT(x) do { cout << x << endl; } while(0)
*/

/***************************************************
 💡 5. MACROS vs INLINE FUNCTIONS
****************************************************/

/*
✅ Macros:
   - Replaced by text before compilation.
   - No type checking.
   - Can lead to subtle bugs.
   - Slightly faster (no function call), but unsafe.

✅ Inline functions (preferred in modern C++):
   - Type safe.
   - Debuggable.
   - Respect scope & namespaces.
*/

// Example Comparison:
#define MAX(a,b) ((a) > (b) ? (a) : (b))       // Macro
inline int maxVal(int a, int b) { return (a > b) ? a : b; } // Inline

/***************************************************
 🔒 6. CONDITIONAL COMPILATION
****************************************************/

// Used to include/exclude parts of code
#define DEBUG

#ifdef DEBUG
    #define LOG(x) cout << "DEBUG: " << x << endl;
#else
    #define LOG(x)
#endif

/*
Usage:
   LOG("Program started");
   // Prints debug info only if DEBUG is defined
*/

/***************************************************
 🧾 7. MULTILINE MACROS
****************************************************/

#define PRINT_PAIR(p) do { \
    cout << "(" << (p).first << ", " << (p).second << ")"; \
} while(0)

/***************************************************
 🧩 8. SUMMARY
****************************************************

✅ Use macros for:
   - Compile-time constants.
   - Template-like shorthand (e.g. all(v)).

⚠️ Avoid macros for:
   - Type-sensitive operations (prefer inline functions).
   - Complex logic.

💬 Modern C++ Tip:
   Use `constexpr`, `inline`, or `auto` instead of macros wherever possible.
****************************************************/




// Macro usage => #define all(container) (container).begin(), (container).end()
// **************************** My Solution [Binary Search] ****************************
#define all(container) (container).begin(), (container).end()

class Solution {
    public:
    // Helper function to check if it's possible to select `k` items
    // such that the minimum gap between selected prices is at least `minGap`.
    bool canSelectWithMinGap(vector<int>& prices, int k, int minGap) {
        int countSelected = 1;
        int lastSelectedPrice = prices[0];
        
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] - lastSelectedPrice >= minGap) {
                ++countSelected;
                lastSelectedPrice = prices[i];
            }
            if (countSelected >= k) return true;
        }
        return false;
    }

    int maximumTastiness(vector<int>& prices, int k) {
        sort(all(prices));

        int result = 0;
        int low = 0;
        int high = prices.back() - prices.front();

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canSelectWithMinGap(prices, k, mid)) {
                result = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return result;
    }
};
// **************************** My Solution [Binary Search] ****************************