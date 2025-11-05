#include <bits/stdc++.h>
using namespace std;

/*
    ----------------------------------------------------------
    LENGTH OF UNION OF 1D SEGMENTS
    ----------------------------------------------------------
    Given multiple line segments [l, r] on a number line,
    find the total length covered by their union.

    Example:
        [1, 5], [3, 7], [8, 10]
        → Union: [1, 7] ∪ [8, 10]
        → Total length = (7-1) + (10-8) = 8
*/

int lengthOfUnion(const vector<pair<int, int>> &segments) {
    int n = segments.size();
    vector<pair<int, bool>> endpoints; // (coordinate, isEnd)

    // Step 1: Store all start and end points
    endpoints.reserve(2 * n);
    for (auto &[start, end] : segments) {
        endpoints.push_back({start, false}); // segment starts
        endpoints.push_back({end, true});    // segment ends
    }

    // Step 2: Sort endpoints by coordinate
    sort(endpoints.begin(), endpoints.end());

    int totalLength = 0;
    int activeCount = 0; // number of overlapping segments

    // Step 3: Sweep line algorithm
    for (int i = 0; i < (int)endpoints.size(); i++) {
        // If we move right and there was at least one active segment,
        // the gap between consecutive coordinates adds to total length
        if (i > 0 && endpoints[i].first > endpoints[i - 1].first && activeCount > 0)
            totalLength += endpoints[i].first - endpoints[i - 1].first;

        // Update active segments count
        if (endpoints[i].second)
            activeCount--;   // segment ends
        else
            activeCount++;   // segment starts
    }

    return totalLength;
}

int main() {
    vector<pair<int, int>> segments = {{1, 5}, {3, 7}, {8, 10}};
    cout << "Total union length = " << lengthOfUnion(segments) << endl;
}
