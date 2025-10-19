/*
Mo's Algorithm — Efficient Offline Range Query Algorithm
---------------------------------------------------------
Used when:
- There are multiple queries asking for something like sum, freq, distinct count, etc.
- The operation can be maintained while adding/removing an element from a range.
*/

/*
Important Variables:
--------------------
arr[]           --> Input array on which queries are asked.
block_size      --> Length of one block; typically sqrt(N).
Query           --> Structure representing each query (l, r, idx).
queries[]       --> All queries stored together and sorted optimally.
answers[]       --> To store results for each query in correct order.
*/

/*
Let's solve: "Count distinct elements in subarray [L, R]"
This example demonstrates Mo’s algorithm in its most classic form.
*/

#include <bits/stdc++.h>
using namespace std;

// Global array and frequency counter
vector<int> arr;
vector<int> frequency(1000001, 0); // assuming array elements <= 1e6
int currentDistinctCount = 0;

// Function to add element at position 'index'
void add(int index) {
    int value = arr[index];
    frequency[value]++;
    if (frequency[value] == 1)  // first time this value appeared
        currentDistinctCount++;
}

// Function to remove element at position 'index'
void remove(int index) {
    int value = arr[index];
    frequency[value]--;
    if (frequency[value] == 0)  // completely removed this value
        currentDistinctCount--;
}

// Function to get current answer
int get_answer() {
    return currentDistinctCount;
}

// Query structure
struct Query {
    int left, right, index;

    // Custom sort logic for Mo’s ordering
    bool operator<(const Query& other) const {
        int thisBlock = left / block_size;
        int otherBlock = other.left / block_size;
        if (thisBlock != otherBlock)
            return thisBlock < otherBlock;
        return (thisBlock & 1) ? (right > other.right) : (right < other.right); 
        // small optimization: alternate order for blocks to reduce moves

        // return right < other.right;  ==> This will also work 
    }
};

// Mo's Algorithm Implementation
vector<int> mos_algorithm(vector<Query>& queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end()); // Sort queries smartly

    int currentL = 0, currentR = -1; // empty range initially

    // Traverse queries in the sorted order
    for (Query q : queries) {
        // Expand to left
        while (currentL > q.left) currentL--, add(currentL);
        // Expand to right
        while (currentR < q.right) currentR++, add(currentR);
        // Shrink from left
        while (currentL < q.left) remove(currentL), currentL++;
        // Shrink from right
        while (currentR > q.right) remove(currentR), currentR--;

        // Store the answer for this query
        answers[q.index] = get_answer();
    }

    return answers;
}

// Driver code to test
int main() {
    int n; cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    int q; cin >> q;
    block_size = sqrt(n);

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].left >> queries[i].right;
        queries[i].index = i;
    }

    vector<int> answers = mos_algorithm(queries);

    for (int ans : answers) cout << ans << "\n";
}





/*
================================================================================
Mo's Algorithm - Pointer Movement and Complexity Intuition
================================================================================

1. Setup:
   - Array size: N
   - Block size: sqrt(N)  --> number of blocks ≈ sqrt(N)
   - Queries: offline, sorted using Mo's order (block of L, then R order)

2. Pointers:
   - L: left boundary of current range
   - R: right boundary of current range

3. Pointer Movements:

   a) L pointer:
      - L moves **forward mostly**, even in worst-case zig-zag inside a block
      - Worst-case inside a block:
        Let s = sqrt(N) (block size)
        L moves as: s,1,s-1,2,... (first query in block may require some back/forth)
        Total L moves for a block: 1 + 2 + 3 + ... + s = s*(s+1)/2 ≈ N (max term)
      - Average L movement per query in a block: ~ sqrt(N)
      - Total L movements for all queries: N (for all blocks combined)

   b) R pointer:
      - R may move forward/backward depending on sorting (normal or snake-order)
      - Max R movements per block: N
      - Average per block: n/sqrt(N) = sqrt(N)
      - Total average R movements for all blocks: sqrt(N) * sqrt(N) = N

4. Total Operations:
   - Each add()/remove() = O(1)
   - Total pointer moves = L moves + R moves ≈ 2N
   - For Q queries, average movement per query ≈ sqrt(N)
   - Overall complexity: O((N + Q) * sqrt(N))

5. Key Takeaways:
   - L moves mostly forward → predictable
   - R moves max sqrt(N) per query on average → efficient
   - Snake-order helps reduce unnecessary jumps of R across blocks
   - Despite linear-looking add/remove code, total work is **sublinear per query** due to sqrt decomposition

6. Visualization (conceptual):
   - L pointer marches forward slowly
   - R pointer zig-zags inside each block
   - Each element touched a **constant number of times** → O((N+Q)√N)

================================================================================
*/
