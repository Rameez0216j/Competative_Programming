/*
    Used when: Number of elements is small (n ≤ 20)
    You need to explore all subsets (2ⁿ)


    ✅ Use in:
        DP + Bitmask
        Subset generation
        Traveling Salesman Problem
*/


for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            // i-th element is included
        }
    }
}


/*    Time: O(2^n * n)
    Space: O(n)
    Use: When n is small (≤ 20) and you need to explore all subsets
    Pre-condition: n is small enough to allow bitmasking

    ✅ Used in:
        Traveling Salesman Problem
        Subset Sum Problem
        Power Set Generation
        Combinatorial Optimization Problems
        DP with Bitmasking
_______________________________________________________________________________________________________________
| Trick                                   | Use                                                               |
| --------------------------------------- | ----------------------------------------------------------------- |
| Binary Search on Answer                 | Key for optimization problems (min time, max length)              |
| Use STL lower\_bound / upper\_bound     | Clean and fast                                                    |
| Think of function f(x)                  | For binary/ternary search, define `f(x)` that satisfies condition |
| Search over position, time, value       | Not just index – be creative                                      |
| Bitmask search                          | If `n` is small (≤ 20), try subset-based brute force              |
| Binary + Greedy                         | A common powerful combo                                           |
_______________________________________________________________________________________________________________

*/

