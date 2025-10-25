#include <bits/stdc++.h>
using namespace std;

// Function to find MEX (Minimum Excludant) of an array
int mex(const vector<int>& A) {
    set<int> b(A.begin(), A.end()); // store elements for fast lookup
    int result = 0;
    while (b.count(result)) // while result exists in the set
        ++result;           // increment to find the missing number
    return result;          // return the MEX
}

/*
    Time Complexity:
        - Inserting n elements into a set: O(n log n)
        - Checking count for result values up to MEX: O(M log n), 
          where M is the MEX value (≤ n if array has elements 0..n-1)
        - Overall: O(n log n)
    
    Space Complexity:
        - O(n) for the set
*/













// Better Complexity
const int MAX_N = 1e6; // maximum value expected in array
// Function to find MEX (Minimum Excludant) using a static boolean array
int mex(const vector<int>& A) {
    static bool used[MAX_N + 1] = { false };

    // Step 1: Mark the numbers present in the array
    for (int x : A) {
        if (x <= MAX_N)
            used[x] = true;
    }

    // Step 2: Find the smallest non-negative integer not in the array
    int result = 0;
    while (used[result])
        ++result;

    // Step 3: Reset the used array for next calls
    for (int x : A) {
        if (x <= MAX_N)
            used[x] = false;
    }

    return result;
}

/*
    Time Complexity:
        - O(n) for marking and clearing elements
        - O(MEX) to find the first unused integer
        - Overall: O(n + MEX) ~ O(n) if MEX ≤ n

    Space Complexity:
        - O(MAX_N) for the boolean array
        - No extra dynamic memory used
*/












// MEX with Updates
#include <bits/stdc++.h>
using namespace std;

// Class to maintain MEX dynamically with updates
class Mex {
private:
    map<int, int> frequency;      // frequency of each number
    set<int> missing_numbers;     // numbers not present in array (candidates for MEX)
    vector<int> A;                // underlying array

public:
    // Constructor: initializes frequency map and missing numbers
    Mex(const vector<int>& A) : A(A) {
        for (int i = 0; i <= A.size(); i++)
            missing_numbers.insert(i);

        for (int x : A) {
            ++frequency[x];
            missing_numbers.erase(x);
        }
    }

    // Returns current MEX (smallest missing number)
    int mex() {
        return *missing_numbers.begin();
    }

    // Updates array at index idx with new_value and updates MEX
    void update(int idx, int new_value) {
        if (--frequency[A[idx]] == 0)
            missing_numbers.insert(A[idx]); // old value becomes missing if frequency 0

        A[idx] = new_value;
        ++frequency[new_value];
        missing_numbers.erase(new_value);    // new value is no longer missing
    }
};

/*
    Time Complexity:
        - Constructor: O(n log n) due to set/map operations
        - mex(): O(1) since set.begin() is constant time
        - update(): O(log n) for insert/erase in set and map

    Space Complexity:
        - O(n) for frequency map, missing_numbers set, and array copy
*/
