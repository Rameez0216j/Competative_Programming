// Solution : https://www.youtube.com/watch?v=BFAdJlloIOQ
// ********************************** My Solution **********************************
/*
    ===========================
    2D Dominance / Bottom-Right Pair Algorithm
    ===========================

    When to Apply:
    --------------
    1. You are given a set of points in 2D space with coordinates (x, y).
    2. You need to count pairs of points (i, j) satisfying a "dominance" condition:
        - Typically: x[j] > x[i] AND y[j] <= y[i]
        - Or in some variations: x[j] > x[i] AND y[j] >= y[i]
    3. This often comes up in problems like:
        - Counting bottom-right points
        - Russian Doll Envelopes (nested intervals)
        - Rectangles or skyline visibility
        - 2D inversion counting
    4. Problem hints:
        - Sorting by one coordinate simplifies checking the other coordinate.
        - Nested loops over points often indicate a "count dominance pairs" scenario.
        - Constraints are small enough (n <= 3000) for O(n^2), otherwise need BIT/Segment Tree.

    What the Algorithm Does:
    ------------------------
    1. Sort all points by x-coordinate in ascending order.
        - If x is equal, sort by y-coordinate in descending order to avoid skipping points on the same vertical line.
    2. For each point i:
        - Initialize maxYBelow to -∞ (or INT_MIN)
        - Iterate over all points j > i:
            a) Skip points where y[j] > y[i] (not bottom-right)
            b) If y[j] > maxYBelow, count it as a valid pair
            c) Update maxYBelow = max(maxYBelow, y[j])
    3. Return the total count of valid pairs.

    Time Complexity:
    ----------------
    - O(n^2) for nested loops over points
    - Sorting: O(n log n)
    - Overall: O(n^2), can be optimized using BIT / Segment Tree to O(n log n) for larger n

    Space Complexity:
    -----------------
    - O(n) for storing markings or max values
    - O(n) for sorting (depends on sort implementation)

    Summary:
    --------
    - This algorithm is essentially a **2D version of inversion counting**.
    - Sort by one axis, scan, and maintain the best value on the other axis to count dominance pairs.
    - Very common in computational geometry and competitive programming problems.


    Examples :

    1. Count the number of pairs of points where one is bottom-right of the other
    - Example: Custom grid dominance problems in CP contests

    2. LeetCode 354 - Russian Doll Envelopes
    - Count how many envelopes can fit into another
    - Sort by width, then apply this dominance logic on height

    3. LeetCode 2281 - Count Artifacts That Can Be Extracted
    - Conceptually similar: dominance in grid points

    4. LeetCode 850 - Rectangle Area II
    - Counting overlapping or nested rectangles using coordinates

    5. Skyline / Building Visibility Problems
    - Count buildings visible from a certain direction
    - Dominance: x increasing, height (y) decreasing

    6. Competitive Programming: Counting 2D inversions
    - Pairs (i, j) where x2 > x1 and y2 < y1
    - Classic 2D inversion count problem

    7. Counting non-overlapping rectangles or points inside another
    - e.g., Given bottom-left points, count how many are enclosed by top-right points

    8. Event Scheduling (2D intervals)
    - Interval start time as x, end time as y
    - Count compatible pairs using this dominance logic

    9. Geometry: Points inside bounding boxes
    - Count points dominated by other points in both axes

    10. LeetCode / CP variations on "dominance counting"
    - Any problem where you need to count pairs satisfying x2 > x1 && y2 <= y1
*/


class Solution {
    public:
    int numberOfPairs(vector<vector<int>>& points) {
        // Sort points by x in ascending order.
        // If x is the same, sort by y in descending order.
        // This ensures points with the same x-axis are processed from top to bottom.
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        int totalPairs = 0;
        int n = points.size();

        for (int i = 0; i < n; i++) {
            int maxYBelow = INT_MIN;  // Tracks the highest y among valid bottom-right points seen so far

            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                // Skip if the next point is above the current one
                if (y2 > y1) continue;

                // Count this as a valid pair if y2 is greater than any previously considered bottom point
                if (y2 > maxYBelow) totalPairs++;

                // Update the maximum y seen below the current y1
                maxYBelow = max(maxYBelow, y2);
            }
        }

        return totalPairs;
    }
};
// ********************************** My Solution **********************************