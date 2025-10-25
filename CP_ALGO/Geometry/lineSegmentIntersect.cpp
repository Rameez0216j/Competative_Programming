#include <bits/stdc++.h>
using namespace std;

// 2D Point / Vector structure
struct Point {
    long long x, y;

    // Constructors
    Point() : x(0), y(0) {}
    Point(long long _x, long long _y) : x(_x), y(_y) {}

    // Vector subtraction
    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    // 2D cross product
    long long cross(const Point& p) const {
        return x * p.y - y * p.x;
    }

    // Cross product of vectors relative to this point
    long long cross(const Point& a, const Point& b) const {
        return (a - *this).cross(b - *this);
    }

    /*
        Segment Intersection using Cross Product

        Idea:
            - Use the current point (P = *this) as the origin.
            - Cross product determines orientation (clockwise, counterclockwise, collinear).
            - Orientation is used to check if two segments AB and CD intersect.

        How it works:
            1. Consider segment CD and points A, B:
                - Compute cross products: CD × CA and CD × CB
                - If signs are different → A and B lie on opposite sides of CD
            2. Consider segment AB and points C, D:
                - Compute cross products: AB × AC and AB × AD
                - If signs are different → C and D lie on opposite sides of AB
            3. If both conditions are true → segments intersect

        Cross product function:

            long long cross(const pt& a, const pt& b) const {
                return (a - *this).cross(b - *this);
            }

        - Computes 2D cross product of vectors PA and PB
            P = *this, A = a, B = b
        - Formula:
            Vector PA = (ax - px, ay - py)
            Vector PB = (bx - px, by - py)
            PA × PB = (ax - px)*(by - py) - (ay - py)*(bx - px)
        - Interpretation:
            PA × PB > 0 → counterclockwise (left turn)
            PA × PB < 0 → clockwise (right turn)
            PA × PB = 0 → collinear
            |PA × PB| → area of parallelogram formed by PA and PB

        Examples:

        1. Counterclockwise:
            P=(0,0), A=(1,0), B=(0,1)
            PA=(1,0), PB=(0,1)
            PA × PB = 1*1 - 0*0 = 1 > 0 → CCW

        2. Clockwise:
            P=(0,0), A=(0,1), B=(1,0)
            PA=(0,1), PB=(1,0)
            PA × PB = 0*0 - 1*1 = -1 < 0 → CW

        3. Collinear:
            P=(0,0), A=(1,1), B=(2,2)
            PA=(1,1), PB=(2,2)
            PA × PB = 1*2 - 1*2 = 0 → collinear
    */


};

// Sign function: returns 1 if positive, 0 if zero, -1 if negative
int sgn(long long x) {
    return (x > 0) - (x < 0);
}

// Check if two 1D intervals [a,b] and [c,d] overlap
bool intervalsOverlap(long long a, long long b, long long c, long long d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}
/*
    Example :
    Given intervals:
            I1 = [a, b]
            I2 = [c, d]

    Step 1: Order the intervals
        Ensure a <= b and c <= d
        I1 = [min(a,b), max(a,b)]
        I2 = [min(c,d), max(c,d)]

    Step 2: Rightmost start and leftmost end
        rightmost_start  = max(a, c)
        leftmost_end     = min(b, d)

    Step 3: Overlap condition
        Intervals overlap ⇔ rightmost_start <= leftmost_end
        Mathematically: max(a, c) <= min(b, d)

    Step 4: Examples
        1. [1,5] and [3,7] → max(1,3)=3 <= min(5,7)=5 → overlap
        2. [1,5] and [5,8] → max(1,5)=5 <= min(5,8)=5 → overlap (touch)
        3. [1,4] and [5,8] → max(1,5)=5 > min(4,8)=4 → no overlap
        4. [5,2] and [4,3] → swapped → [2,5] and [3,4] → overlap

    ✅ Applications:
        1. "My Calendar" problems on LeetCode – checking if a new event overlaps existing events
        2. Meeting rooms / scheduling problems – detect conflicts between meeting times
        3. Any problem involving 1D interval conflicts or merging intervals
*/


// Check if two line segments AB and CD intersect [AB formed by points a,b and CD fromed by points c,d]
bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    // Collinear case
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0) {
        return intervalsOverlap(a.x, b.x, c.x, d.x) &&
               intervalsOverlap(a.y, b.y, c.y, d.y);
    }

    // General case: check if segments straddle each other 
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}
/*
    Function: segmentsIntersect

    Purpose:
        Checks whether two 2D line segments AB and CD intersect.

    Inputs:
        Segment 1: A -> B
        Segment 2: C -> D

    Method:
        Uses vector cross products to determine orientation and intersection.

---------------------------------------------------------

    Step 1: Handle the collinear case
        - If points are collinear, segments may still intersect if their projections on x and y axes overlap.
        - Check collinearity using cross product:
            c.cross(a, d) == 0 && c.cross(b, d) == 0
            - Here, c.cross(a, d) = (a - c) × (d - c)
            - Zero means points a, d, c are collinear
        - If collinear, use 1D interval overlap check for both axes:
            intervalsOverlap(a.x, b.x, c.x, d.x)
            intervalsOverlap(a.y, b.y, c.y, d.y)
        - Intersection exists only if **both x and y intervals overlap**

---------------------------------------------------------

    Step 2: General case (non-collinear segments)
        - Use orientation tests to see if segments "straddle" each other:
            1. Check orientations of points C and D w.r.t line AB:
                sgn(a.cross(b, c)) != sgn(a.cross(b, d))
                - If signs differ, C and D are on opposite sides of line AB
            2. Check orientations of points A and B w.r.t line CD:
                sgn(c.cross(d, a)) != sgn(c.cross(d, b))
                - If signs differ, A and B are on opposite sides of line CD
        - If both conditions are true, segments intersect.

---------------------------------------------------------

    Step 3: Summary (mathematical)
        Let:
            AB = vector from A to B
            CD = vector from C to D

        Collinear condition:
            (A, B, C) and (A, B, D) are collinear (cross product zero)
            → Check if 1D projections on x and y axes overlap

        General condition:
            Intersection exists iff:
                (C and D lie on opposite sides of AB) AND
                (A and B lie on opposite sides of CD)

---------------------------------------------------------

    Step 4: Examples

    1. Intersecting segments:
        A(0,0), B(4,4), C(0,4), D(4,0)
        - Cross products:
            a.cross(b,c) = 0*4 - 0*4 = 0 → orientation check
            General case yields true → segments intersect

    2. Non-intersecting segments:
        A(0,0), B(2,2), C(3,3), D(5,5)
        - Collinear case: true, but x and y intervals do not overlap → false
        - General case also false → segments do not intersect

    3. Touching at endpoints:
        A(0,0), B(2,2), C(2,2), D(4,0)
        - Collinear check fails
        - Orientation test true → segments intersect at a point
*/

