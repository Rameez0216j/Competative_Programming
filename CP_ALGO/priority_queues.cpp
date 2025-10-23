#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
1️⃣ USING STRUCT (Functor Comparator)
----------------------------------------------------
This is the traditional and most common way.
You define a struct with operator() overloaded
to compare two elements.
*/
struct CompareByFirst {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        // Return true if a should come AFTER b (for max-heap behavior)
        // For min-heap, flip the sign
        return a[0] < b[0];
    }
};

/*
----------------------------------------------------
2️⃣ USING LAMBDA FUNCTION (Modern C++11+)
----------------------------------------------------
Lambdas are short, inline, and flexible.
We define a lambda comparator and use decltype(cmp)
as the comparator type.
*/
void lambdaComparatorExample() {
    // Lambda comparator
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];  // max-heap (largest first element on top)
    };

    // Declaring priority_queue using decltype of the lambda
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

    pq.push({5, 2});
    pq.push({1, 9});
    pq.push({3, 4});

    cout << "\n--- Lambda Comparator (Max-Heap) ---\n";
    while (!pq.empty()) {
        vector<int> top = pq.top();
        pq.pop();
        cout << "[" << top[0] << ", " << top[1] << "]\n";
    }

    // To make it a MIN-HEAP, just flip comparison:
    // return a[0] > b[0];
}

/*
----------------------------------------------------
3️⃣ USING NORMAL FUNCTION POINTER COMPARATOR
----------------------------------------------------
You define a standalone function and use its pointer
as the comparator. You must specify the exact function
pointer type in the priority_queue declaration.
*/

// Function comparator
bool compareVectors(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];  // max-heap based on first element
}

void functionPointerComparatorExample() {
    // Type of comparator = bool(*)(const vector<int>&, const vector<int>&)
    priority_queue<
        vector<int>, 
        vector<vector<int>>, 
        bool(*)(const vector<int>&, const vector<int>&)
    > pq(compareVectors);  // Pass function name (decays to pointer)

    pq.push({5, 2});
    pq.push({1, 9});
    pq.push({3, 4});

    cout << "\n--- Function Pointer Comparator (Max-Heap) ---\n";
    while (!pq.empty()) {
        vector<int> top = pq.top();
        pq.pop();
        cout << "[" << top[0] << ", " << top[1] << "]\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example 1: Using Struct Comparator
    {
        priority_queue<vector<int>, vector<vector<int>>, CompareByFirst> pq;

        pq.push({5, 2});
        pq.push({1, 9});
        pq.push({3, 4});

        cout << "--- Struct Comparator (Max-Heap) ---\n";
        while (!pq.empty()) {
            vector<int> top = pq.top();
            pq.pop();
            cout << "[" << top[0] << ", " << top[1] << "]\n";
        }
    }

    // Example 2: Using Lambda Comparator
    lambdaComparatorExample();

    // Example 3: Using Function Pointer Comparator
    functionPointerComparatorExample();

    return 0;
}
