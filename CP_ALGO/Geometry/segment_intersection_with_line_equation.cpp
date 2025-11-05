#include <bits/stdc++.h>
using namespace std;

/*
    SEGMENT INTERSECTION USING LINE EQUATIONS
    -----------------------------------------

    This code handles all intersection cases:
      1. Proper intersection (crossing)
      2. Collinear overlap (segments lying on the same line)
      3. Floating-point safe checks using EPS (tolerance)
*/

const double EPS = 1E-9;

// ===================== POINT STRUCT ===================== //
struct pt {
    double x, y;

    // Operator overload for sorting / comparison
    bool operator<(const pt& p) const {
        // Compare x first, then y with precision tolerance
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

// ===================== LINE STRUCT ===================== //
struct line {
    double a, b, c; // Equation: a*x + b*y + c = 0

    line() {}
    line(pt p, pt q) {
        // Construct line from two points (p, q)
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm(); // Normalize coefficients for stability
    }

    // Normalize so that sqrt(a^2 + b^2) = 1
    void norm() {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    
    /*  
        ---------------------------------------------------------------
        🧠 Concept: Distance of a Point from a Line
        ---------------------------------------------------------------
        
        For a line:
        a*x + b*y + c = 0
        
        and a point:
        P(x0, y0)
        
        The perpendicular (shortest) distance from the point to the line is:
        
        distance = |a*x0 + b*y0 + c| / sqrt(a^2 + b^2)
    */
   // Signed distance of point 'p' from the line
   double dist(pt p) const {
       return a * p.x + b * p.y + c; // already normalized so just substitute the point
   }
};

// ===================== HELPER FUNCTIONS ===================== //

// Determinant of 2x2 matrix
double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

// Check if x lies between l and r (inclusive, with tolerance)
inline bool betw(double l, double r, double x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

// Check if two 1D intervals [a,b] and [c,d] overlap
inline bool intersect_1d(double a, double b, double c, double d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

// ===================== MAIN INTERSECTION LOGIC ===================== //
bool intersect(pt a, pt b, pt c, pt d, pt& left, pt& right) {
    // Step 1: Quick reject test (bounding boxes)
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;

    // Step 2: Represent both segments as lines
    line m(a, b), n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);

    // Step 3: Handle collinear and parallel lines
    if (abs(zn) < EPS) {
        // Check if they lie on different lines
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
            return false; // Parallel and distinct

        // They are collinear → check overlapping part
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);

        left = max(a, c);
        right = min(b, d);

        // If they overlap at least at one point
        return true;
    }

    // Step 4: Proper intersection
    // Solve for intersection point using determinants
    left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
    left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;

    // Step 5: Check if intersection point lies within both segments
    return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
           betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
}


/*
    📘 Meaning of 'left' and 'right' points:

    There are two possible types of intersections:

    1️⃣ Proper Intersection:
    - The segments cross at exactly one point.
    - Both 'left' and 'right' store that single intersection point.

    2️⃣ Collinear Overlap:
    - The segments lie on the same line and overlap partially.
    - 'left' → starting endpoint of the overlap
    - 'right' → ending endpoint of the overlap
    - Example:
        [1----5] and [3----7] → overlap is [3----5]
        so left = (3,0), right = (5,0)

    Hence:
    - For single-point intersection → left == right
    - For overlapping segment → [left, right] gives the overlapping region
*/

int main() {
    pt a{0, 0}, b{4, 4}, c{0, 4}, d{4, 0}, left, right;

    if (intersect(a, b, c, d, left, right)) {
        cout << "Segments intersect at: (" << left.x << ", " << left.y << ") "<<"till" << " (" << right.x << ", " << right.y << ")\n";
    } else {
        cout << "Segments do not intersect.\n";
    }

    return 0;
}









/*
    ----------------------------------------------------------
        🧠 MATHEMATICAL INTERPRETATION:

        Line equation from two points (x1,y1) & (x2,y2):

            a = y1 - y2
            b = x2 - x1
            c = -a*x1 - b*y1

            → a*x + b*y + c = 0

        Intersection of two lines:
            m: a1*x + b1*y + c1 = 0
            n: a2*x + b2*y + c2 = 0

            Determinant form:

            zn = a1*b2 - b1*a2
            If zn = 0 → parallel or coincident

            Intersection point:
                x = -det(c1,b1,c2,b2) / zn
                y = -det(a1,c1,a2,c2) / zn

        Segment condition:
            Intersection point must lie within both segments’
            bounding boxes → checked via betw() and intersect_1d().

    ----------------------------------------------------------
        ✅ EXAMPLES:

        1. Proper intersection:
            A(0,0), B(4,4)
            C(0,4), D(4,0)
            → Intersect at (2,2)

        2. Collinear overlapping:
            A(0,0), B(4,4)
            C(2,2), D(6,6)
            → Overlap between [2,2] and [4,4]

        3. Parallel non-intersecting:
            A(0,0), B(4,0)
            C(0,1), D(4,1)
            → Parallel, no intersection
    ----------------------------------------------------------
*/



