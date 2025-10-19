#include <bits/stdc++.h>
using namespace std;

int maxProductSubarray(vector<int>& arr) {
    int maxProd = arr[0];
    int currentMax = arr[0];
    int currentMin = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < 0) swap(currentMax, currentMin); // flip when negative
        
        currentMax = max(arr[i], currentMax * arr[i]);
        currentMin = min(arr[i], currentMin * arr[i]);
        
        maxProd = max(maxProd, currentMax);
    }

    return maxProd;
}

int main() {
    vector<int> arr = {2,3,-2,4};
    cout << "Maximum Product Subarray: " << maxProductSubarray(arr) << endl;
}
