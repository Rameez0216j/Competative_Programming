#include <bits/stdc++.h>
using namespace std;

const double EPS = 1E-9;

/* -------------------------------------------------------------
   🧭 Structure: Point (pt)
   Represents a point or vector in 2D space.
------------------------------------------------------------- */
struct pt {
    double x, y;

    // For coordinate comparison (used in sorting or min/max)
    bool operator<(const pt& p) const {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

/* -------------------------------------------------------------
   📏 Structure: Line
   Represents a line in the general form:
       a*x + b*y + c = 0
------------------------------------------------------------- */
struct line {
    double a, b, c;

    line() {}

    // Construct line from two points p and q (segment endpoints)
    line(pt p, pt q) {
        /*
            Formula derivation:

            Line through points (x1, y1) and (x2, y2):
                (y1 - y2)*x + (x2 - x1)*y + (x1*y2 - x2*y1) = 0

            Therefore:
                a = y1 - y2
                b = x2 - x1
                c = -(a*x1 + b*y1)
        */
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();  // Normalize to unit vector form
    }

    // Normalize line coefficients so that √(a² + b²) = 1
    void norm() {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    /*
        📐 Distance of point p(x, y) from the line:
            dist = a*x + b*y + c
        Since we normalized (a, b, c), this gives the
        signed perpendicular distance directly.

        Sign meaning:
            +ve → point lies on one side of the line
            -ve → point lies on the opposite side
             0  → point lies exactly on the line
    */
    double dist(pt p) const { return a * p.x + b * p.y + c; }
};

/* -------------------------------------------------------------
   ⚙️ Determinant Function
   Used to solve the intersection point of two lines.
   det(a, b, c, d) = a*d - b*c
------------------------------------------------------------- */
double det(double a, double b, double c, double d) {
    return a * d - b * c;
}

/* -------------------------------------------------------------
   ✅ Check if x lies between l and r (with EPS tolerance)
------------------------------------------------------------- */
inline bool betw(double l, double r, double x) {
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

/* -------------------------------------------------------------
   ✅ Check if two 1D segments [a,b] and [c,d] overlap
------------------------------------------------------------- */
inline bool intersect_1d(double a, double b, double c, double d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

/* -------------------------------------------------------------
   🚦 Segment Intersection Function
   Returns true if segments AB and CD intersect.
   If they do, 'left' and 'right' store intersection points.
------------------------------------------------------------- */
bool intersect(pt a, pt b, pt c, pt d, pt& left, pt& right) {
    // Step 1: Quick reject (if projections on x or y axes do not overlap)
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;

    // Step 2: Build line equations for both segments
    line m(a, b);
    line n(c, d);

    // Step 3: Compute determinant (for solving intersection)
    double zn = det(m.a, m.b, n.a, n.b);

    // Step 4: Handle parallel or collinear cases
    if (abs(zn) < EPS) {
        // Lines are parallel
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
            return false;  // Strictly parallel (no overlap)

        // Collinear case — check segment overlap
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } 
    else {
        /*
            Step 5: Compute intersection point

            Solving the system:
                m.a*x + m.b*y + m.c = 0
                n.a*x + n.b*y + n.c = 0

            Using determinant formula:
                x = -det(m.c, m.b, n.c, n.b) / det(m.a, m.b, n.a, n.b)
                y = -det(m.a, m.c, n.a, n.c) / det(m.a, m.b, n.a, n.b)
        */
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;

        // Step 6: Check if intersection point lies within both segments (may be the intersection is about extended lines)
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}

/* -------------------------------------------------------------
   🧮 Mathematical Notes

   Line Equation:
       For two points (x1, y1), (x2, y2):
           a = y1 - y2
           b = x2 - x1
           c = -(a*x1 + b*y1)
       => a*x + b*y + c = 0

   Normalization:
       Divide (a, b, c) by sqrt(a² + b²)
       Ensures line direction vector (a, b) has length = 1
       Then dist(p) gives perpendicular distance directly.

   Intersection:
       Solve two linear equations using determinant rule:
           a1*x + b1*y + c1 = 0
           a2*x + b2*y + c2 = 0
       → x = -det(c1,b1,c2,b2) / det(a1,b1,a2,b2)
         y = -det(a1,c1,a2,c2) / det(a1,b1,a2,b2)
------------------------------------------------------------- */

int main() {
    pt a{0, 0}, b{4, 4}, c{0, 4}, d{4, 0};
    pt left, right;

    if (intersect(a, b, c, d, left, right)) {
        cout << fixed << setprecision(6);
        cout << "Segments intersect at: (" << left.x << ", " << left.y << ")\n";
    } else {
        cout << "Segments do not intersect.\n";
    }
}
