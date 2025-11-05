/*
    🧠 Circle–Circle Intersection — Mathematical Intuition

    We are given two circles:
    1️⃣  x² + y² = r₁²
    2️⃣  (x - x₂)² + (y - y₂)² = r₂²

    ----------------------------------------
    🎯 Step 1: Subtract (1) from (2)
    ----------------------------------------
    This eliminates x² and y²:

    -2x₂·x - 2y₂·y + (x₂² + y₂² + r₁² - r₂²) = 0

    ----------------------------------------
    🎯 Step 2: Rearrange into line form
    ----------------------------------------
    A·x + B·y + C = 0
    where:
        A = -2x₂
        B = -2y₂
        C = x₂² + y₂² + r₁² - r₂²

    This line represents **all possible intersection points**
    between the two circles.

    💡 Why?
    Because any point (x, y) lying on both circles
    must satisfy both circle equations.
    Subtracting them removes the squared terms,
    leaving the *linear relation* that those common points follow.

    Hence, this line passes through **every intersection point**
    of the two circles.

    ----------------------------------------
    ⚠️ Special Case — Coincident Centers
    ----------------------------------------
    If the centers coincide (x₂ = y₂ = 0):
    → Equation reduces to C = r₁² - r₂² = 0

    • If r₁ == r₂ → Infinite intersections (same circle)
    • If r₁ ≠ r₂ → No intersection
*/


#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    // Step 0: Check if circles coincide
    if (fabs(x1 - x2) < EPS && fabs(y1 - y2) < EPS) {
        if (fabs(r1 - r2) < EPS) {
            cout << "Circles coincide (infinitely many intersection points)\n";
        } else {
            cout << "No intersection (same center, different radii)\n";
        }
        return 0;
    }


    // Step 1: Move first circle to origin by translating coordinates
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Derived line equation: A*x + B*y + C = 0 (from circle subtraction)
    double A = -2 * dx;
    double B = -2 * dy;
    double C = dx * dx + dy * dy + r1 * r1 - r2 * r2;

    // Step 2: Solve circle (x^2 + y^2 = r1^2) with line (A*x + B*y + C = 0)
    double a = A, b = B, c = C;

    // Foot of perpendicular from circle center (0,0) to line
    double x0 = -a * c / (a * a + b * b);
    double y0 = -b * c / (a * a + b * b);

    double distanceSquared = c * c / (a * a + b * b);

    // Step 3: Determine intersection type
    if (c * c > r1 * r1 * (a * a + b * b) + EPS) {
        cout << "No intersection points\n";
    } 
    else if (fabs(c * c - r1 * r1 * (a * a + b * b)) < EPS) {
        cout << "One intersection point (tangent):\n";
        // Shift back to original coordinates
        cout << fixed << setprecision(6)
             << x0 + x1 << " " << y0 + y1 << "\n";
    } 
    else {
        // Two intersection points
        double offset = sqrt(r1 * r1 - distanceSquared);
        double mult = offset / sqrt(a * a + b * b);

        double x1_int = x0 + b * mult;
        double y1_int = y0 - a * mult;
        double x2_int = x0 - b * mult;
        double y2_int = y0 + a * mult;

        cout << "Two intersection points:\n";
        cout << fixed << setprecision(6);
        cout << x1_int + x1 << " " << y1_int + y1 << "\n";
        cout << x2_int + x1 << " " << y2_int + y1 << "\n";
    }

    return 0;
}
