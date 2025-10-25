#include <bits/stdc++.h>
using namespace std;

//------------------------------------
// STRUCT: Point representation
//------------------------------------
struct pt {
    double x, y;
    bool operator==(pt const& t) const {
        return x == t.x && y == t.y;
    }
};

//------------------------------------
// FUNCTION: Orientation test
//
// Formula used in orientation():
//     v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)
//
// Mathematical form:
//     2 * (Signed Area of △ABC) = 
//         x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)
//
// Interpretation of 'v':
//     v > 0  → Counter-Clockwise (CCW)
//     v < 0  → Clockwise (CW)
//     v = 0  → Collinear
//
// When points a, b, c are sorted by x-axis:
//   - The sign of 'v' directly tells whether the turn from a → b → c
//     bends *upward* (CCW) or *downward* (CW) relative to the x-axis.
//
// Geometric meaning:
//   - This is equivalent to the determinant of the 3×3 matrix:
//         | x1  y1  1 |
//         | x2  y2  1 |  =  2 * SignedArea
//         | x3  y3  1 |
/*
    What CCW and CW mean

    - Imagine standing at point 'a' and looking towards point 'b'.
    - If you must turn left to go from 'b' to 'c', that’s Counter-Clockwise (CCW).
    - If you must turn right to go from 'b' to 'c', that’s Clockwise (CW).
*/

//------------------------------------
int orientation(pt a, pt b, pt c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

//------------------------------------
// FUNCTION: Check clockwise condition
// include_collinear = true → allows collinear points
//------------------------------------
bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}

//------------------------------------
// FUNCTION: Check collinearity
//------------------------------------
bool collinear(pt a, pt b, pt c) { 
    return orientation(a, b, c) == 0; 
}

//------------------------------------
// FUNCTION: Convex Hull (Graham Scan variant)
//------------------------------------
void convex_hull(vector<pt>& a, bool include_collinear = false) {
    // Step 1: Find lowest (y) point — pivot for sorting
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });

    // Step 2: Sort points by polar angle with respect to p0
    // Points are sorted in increasing polar angle, which is generally counterclockwise around p0.
    // Polar angle = angle between line p0→point and x-axis.
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            // If collinear, closer point comes first
            return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y)  // distance square from p0 to a
                 < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);  // distance square from p0 to b
        return o < 0;
    });

    // Step 3: If including collinear points, reverse the last section  [as point at farther distance is kept last so using convex hull will eliminate the nearer coollinear points, but the tour should end in p0 then clockwise rotating including colliner points from nearer to farther and at ending coming from collinear farther point at the end to p0 again]
    if (include_collinear) {
        int i = (int)a.size() - 1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin() + i + 1, a.end());
    }

    // Step 4: Build convex hull
    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size() - 2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    // Step 5: Remove duplicate point if only two unique points
    if (!include_collinear && st.size() == 2 && st[0] == st[1])
        st.pop_back();

    a = st;
}

/*
------------------------------------
🧠 MATH NOTES
------------------------------------
1️⃣ Orientation formula:
   orientation(a, b, c) = sign( (b - a) × (c - a) )
   where × is the 2D cross product:
        (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)

   > 0  → Counter-clockwise turn
   < 0  → Clockwise turn
   = 0  → Collinear points

2️⃣ Convex Hull
   - The convex hull of a set of points is the smallest convex polygon
     that contains all the points.

   - This implementation uses Graham’s Scan:
     a) Find pivot (lowest y)
     b) Sort by polar angle around pivot
     c) Use a stack to build the hull, maintaining only left turns (CCW)

------------------------------------
⏱️ Time Complexity:
    Sorting: O(n log n)
    Scanning: O(n)
    ✅ Total: O(n log n)

💾 Space Complexity:
    O(n)
------------------------------------
*/





/*
Graham Scan vs Monotone Chain (a.k.a. Andrew's Algorithm)

1. Graham Scan:
   - Starts from the pivot point (usually the point with lowest y, then lowest x).
   - Sorts all points by **polar angle** with respect to pivot.
   - Traverses points in order, maintaining a **stack**.
   - Adds points making counter-clockwise (CCW) turns.
   - Removes points making clockwise (CW) turns.
   - Result: The stack ends up containing the convex hull points in **CCW order**, starting and ending at the pivot.

2. Monotone Chain (MonteCycle):
   - Sorts points **lexicographically** (x, then y).
   - Constructs **upper hull** and **lower hull** separately:
       - Upper hull: top boundary from leftmost to rightmost point.
       - Lower hull: bottom boundary from leftmost to rightmost point.
   - Combines upper and lower hulls and removes duplicates.
   - Result: Convex hull points in order along the polygonal boundary.
   - Advantage: Handles collinear points easily and simpler than polar angle sort.

Key Difference:
- Graham Scan: CCW rotation from pivot, uses stack.
- Monotone Chain: Upward and downward boundaries, uses simple vector construction.
*/

