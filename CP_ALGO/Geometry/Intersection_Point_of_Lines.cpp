#include <bits/stdc++.h>
using namespace std;

// 2D Point structure
struct pt {
    double x, y;  // coordinates
};

// Line represented in standard form: a*x + b*y + c = 0
struct line {
    double a, b, c;
};

const double EPS = 1e-9; // tolerance for floating point comparisons

// 2x2 determinant: |a b|
//                   |c d|
double det(double a, double b, double c, double d) {
    return a*d - b*c;
}

// Intersection of two lines using Cramer's Rule
bool intersect(line m, line n, pt & res) {
    double zn = det(m.a, m.b, n.a, n.b); // determinant of coefficients

    // If determinant ≈ 0, lines are parallel (no unique intersection)
    if (abs(zn) < EPS)
        return false;

    // Solve for intersection point (x, y)
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}

/*
    Example:

    Line 1: x + y - 2 = 0 → a=1, b=1, c=-2
    Line 2: x - y + 0 = 0 → a=1, b=-1, c=0

    determinant zn = det(1,1,1,-1) = -2 ≠ 0 → lines intersect
    Solve using Cramer's rule:
        x = -det(-2,1,0,-1)/(-2) = 1
        y = -det(1,-2,1,0)/(-2) = 1
    Intersection point: (1,1)
*/

// Check if two lines are parallel
bool parallel(line m, line n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS;
}
/*
    Mathematical explanation:
    - Lines are parallel if determinant of coefficients = 0
    - det(a1,b1,a2,b2) = a1*b2 - a2*b1
    - Represents slope comparison: a1/b1 == a2/b2
*/

// Check if two lines are equivalent (coincident)
bool equivalent(line m, line n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS          // parallel
        && abs(det(m.a, m.c, n.a, n.c)) < EPS          // proportional c for x
        && abs(det(m.b, m.c, n.b, n.c)) < EPS;         // proportional c for y
}
/*
    Mathematical explanation:
    - Two lines are equivalent if they are parallel AND
      their constants c are in the same ratio as the coefficients a and b
    - Essentially: a1/a2 = b1/b2 = c1/c2
*/

// Usage example
int main() {
    line l1 = {1, 1, -2}; // x + y - 2 = 0
    line l2 = {1, -1, 0}; // x - y = 0
    pt intersection;

    if (intersect(l1, l2, intersection)) {
        cout << "Intersection: (" << intersection.x << "," << intersection.y << ")\n";
    } else if (parallel(l1, l2)) {
        cout << "Lines are parallel\n";
        if (equivalent(l1, l2))
            cout << "Lines are coincident\n";
    }

    return 0;
}


// Crammers rule 
/*
    Line1: a1 x + b1 y = -c1
    Line2: a2 x + b2 y = -c2

        det([-c1, b1], 
            [-c2, b2]) 
    x = --------------
        det([a1, b1],
            [a2, b2])


        det([a1,-c1], 
            [a2,-c2]) 
    y = --------------
        det([a1, b1],
            [a2, b2])

    here [a1,a2] and [b1,b2] in numerator match the position with denominator 
    only change is [-c1,-c2]

*/