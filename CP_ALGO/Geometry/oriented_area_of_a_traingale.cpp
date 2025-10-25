#include <bits/stdc++.h>
using namespace std;

// 2D Point structure
struct point2d {
    double x, y;

    // Vector subtraction
    point2d operator-(const point2d &p) const {
        return {x - p.x, y - p.y};
    }
};

// 2D cross product
double cross(const point2d &p1, const point2d &p2) {
    // Computes p1.x * p2.y - p1.y * p2.x
    return p1.x * p2.y - p1.y * p2.x;
}

/* -------------------------------------------------------------
    🧮 Oriented Area of Triangle (using parallelogram area)
    
    Given triangle with points p1, p2, p3:
        - Compute cross product of vectors (p2 - p1) and (p3 - p2)
        - Returns signed area of parallelogram formed by the vectors
        - Triangle area = |signed_area| / 2
------------------------------------------------------------- */
double signed_area_parallelogram(point2d p1, point2d p2, point2d p3) {
    return cross(p2 - p1, p3 - p2);
}

/* -------------------------------------------------------------
    ✅ Area of Triangle (always positive)
------------------------------------------------------------- */
double triangle_area(point2d p1, point2d p2, point2d p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

/* -------------------------------------------------------------
    ⏩ Orientation Check
    
    Clockwise: signed area < 0
    Counterclockwise: signed area > 0
    Collinear: signed area = 0
------------------------------------------------------------- */
bool clockwise(point2d p1, point2d p2, point2d p3) {
    return signed_area_parallelogram(p1, p2, p3) < 0;
}

bool counter_clockwise(point2d p1, point2d p2, point2d p3) {
    return signed_area_parallelogram(p1, p2, p3) > 0;
}

bool collinear(point2d p1, point2d p2, point2d p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) < 1e-9;
}

/* -------------------------------------------------------------
    📌 Example usage:
------------------------------------------------------------- */
int main() {
    point2d A{0, 0}, B{4, 0}, C{0, 3};

    cout << "Signed parallelogram area: " << signed_area_parallelogram(A, B, C) << "\n";
    cout << "Triangle area: " << triangle_area(A, B, C) << "\n";

    if (clockwise(A, B, C)) cout << "Points are clockwise\n";
    if (counter_clockwise(A, B, C)) cout << "Points are counter-clockwise\n";
    if (collinear(A, B, C)) cout << "Points are collinear\n";

    return 0;
}






/*
    Oriented Area of a Triangle (2D)

    Let three points of a triangle be:
        P1 = (x1, y1)
        P2 = (x2, y2)
        P3 = (x3, y3)

    Signed area formula using cross product of vectors from P1:

        area_signed = (P2 - P1) × (P3 - P2)
                    = (x2 - x1)*(y3 - y2) - (y2 - y1)*(x3 - x2)

    Explanation:
        - This gives twice the area of the triangle with a sign.
        - Positive sign → points are in counterclockwise order (CCW)
        - Negative sign → points are in clockwise order (CW)
        - Zero → points are collinear

    Triangle Area (always positive):
        area = |area_signed| / 2.0

    Orientation checks:
        clockwise(P1, P2, P3)         → area_signed < 0
        counter_clockwise(P1, P2, P3) → area_signed > 0
        collinear(P1, P2, P3)         → area_signed == 0
*/
