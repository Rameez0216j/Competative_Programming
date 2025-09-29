#include <bits/stdc++.h>
using namespace std;

/*
    FOUR TYPES OF NEXT ELEMENT ALGORITHMS

    1. Next Greater Element (nearest strictly greater to the right)
    2. Next Smaller Element (nearest strictly smaller to the right)
    3. Smallest Greater to the Right (≥ value, Odd-Jumps style)
    4. Largest Smaller to the Right (≤ value, Even-Jumps style)

    Each function returns a vector of indices pointing to the next element.
    - If no valid next element exists, the value is -1.
*/

vector<int> nextGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n, -1);
    stack<int> st; // stores indices

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[i] >= arr[st.top()]) st.pop();
        if (!st.empty()) nge[i] = st.top();
        st.push(i);
    }
    return nge;
}

vector<int> nextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st; // stores indices

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[i] <= arr[st.top()]) st.pop();
        if (!st.empty()) nse[i] = st.top();
        st.push(i);
    }
    return nse;
}

vector<int> smallestGreaterRight(const vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);

    // Sort indices by value ascending (for Odd Jumps style)
    sort(indices.begin(), indices.end(), [&](int i, int j){
        if(arr[i] == arr[j]) return i < j;
        return arr[i] < arr[j];
    });

    stack<int> st;
    for(int i : indices) {
        while(!st.empty() && i > st.top()) {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

vector<int> largestSmallerRight(const vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);

    // Sort indices by value descending (for Even Jumps style)
    sort(indices.begin(), indices.end(), [&](int i, int j){
        if(arr[i] == arr[j]) return i < j;
        return arr[i] > arr[j];
    });

    stack<int> st;
    for(int i : indices) {
        while(!st.empty() && i > st.top()) {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

// Utility function to print result in a readable format
void printResult(const vector<int>& arr, const vector<int>& res, const string& title) {
    cout << title << ":\n";
    for (int i = 0; i < arr.size(); i++) {
        cout << "Index " << i << " (" << arr[i] << ") -> ";
        if (res[i] == -1) cout << "-1\n";
        else cout << res[i] << " (" << arr[res[i]] << ")\n";
    }
    cout << "\n";
}

int main() {
    vector<int> arr = {10, 13, 12, 14, 15, 11};

    auto nge = nextGreater(arr);
    auto nse = nextSmaller(arr);
    auto sgr = smallestGreaterRight(arr);
    auto lsr = largestSmallerRight(arr);

    printResult(arr, nge, "Next Greater Element (nearest strictly greater)");
    printResult(arr, nse, "Next Smaller Element (nearest strictly smaller)");
    printResult(arr, sgr, "Smallest Greater to Right (Odd Jumps style)");
    printResult(arr, lsr, "Largest Smaller to Right (Even Jumps style)");

    return 0;
}