/*
🟢 INTUITION: CIRCLE–LINE INTERSECTION

We want to find where a LINE and a CIRCLE touch or cross each other.

----------------------------------------------------------
🎯 Step 1: Move our Circle to a Nice Place
----------------------------------------------------------
Let’s imagine our circle is sitting at the center (0, 0) — nice and easy.
If it’s not there, we can just shift everything so that it is.

So:
    Circle: x² + y² = r²
    Line:   A*x + B*y + C = 0

Here (A, B) tells us how tilted the line is, and C tells us how far
it is from the center (0, 0).

----------------------------------------------------------
📏 Step 2: Find the Point on the Line Closest to the Center
----------------------------------------------------------
We drop a perpendicular from the circle’s center (0, 0) to the line.

The point where it touches the line is called the **foot of perpendicular**,
and we’ll call it (x₀, y₀).

The distance from the center to the line is:

    d₀ = |C| / √(A² + B²)

That’s how far the line is from the circle’s center.

Now, the point (x₀, y₀) lies along the direction of the normal vector (A, B),
but scaled down so it touches the line.

That gives:

    x₀ = -A*C / (A² + B²)
    y₀ = -B*C / (A² + B²)

(We use a minus sign because the line’s C term decides which side of origin it’s on.)

----------------------------------------------------------
🔍 Step 3: Check How the Line and Circle Interact
----------------------------------------------------------
Now, depending on how big the radius (r) is compared to that distance (d₀),
we can tell how many intersection points there are:

    👉 If d₀ > r → the line is outside the circle → no intersection.
    👉 If d₀ = r → the line just touches → one point (tangent).
    👉 If d₀ < r → the line cuts the circle → two intersection points.

----------------------------------------------------------
📏 Step 4: Find Half the Chord Length (small segment inside circle)
----------------------------------------------------------
The line cuts the circle and forms a chord.
The midpoint of that chord is our (x₀, y₀).
We need to find how far to move along the line to reach the two intersection points.

By Pythagoras theorem (r, d₀, and half-chord make a right triangle):

    r² = d₀² + d²
    => d = √(r² - d₀²)
       = √(r² - C² / (A² + B²))

This 'd' is the half-length of the chord (distance from midpoint to intersection).

----------------------------------------------------------
📐 Step 5: Move Along the Line to Get Intersection Points
----------------------------------------------------------
The line’s **direction vector** (the way the line goes) is perpendicular
to its normal (A, B). So, a direction vector for the line is (-B, A).

Now, to move from the midpoint (x₀, y₀) to the actual intersection points,
we go "d" units along (-B, A), both in positive and negative directions.

So we find a scaling factor ‘m’ that converts (-B, A) into the proper step length:

    m = √(d² / (A² + B²))

----------------------------------------------------------
🧮 Step 6: The Final Intersection Points
----------------------------------------------------------
    aₓ = x₀ + B*m
    a_y = y₀ - A*m
    bₓ = x₀ - B*m
    b_y = y₀ + A*m

Those are our two intersection points with the circle.

----------------------------------------------------------
✨ WHY GEOMETRY IS BETTER THAN PURE ALGEBRA
----------------------------------------------------------
If we solved this problem using only equations (algebra),
we’d have to deal with quadratic formulas and risk floating-point errors.

But with this **geometric method**, we just use perpendicular distances
and directions — making it **simpler, cleaner, and more accurate**.
*/







// ********************   VERY IMPORTANT NOTE   ******************** 
/*
🧠 Concept: Shifting Coordinate System in Geometry

Suppose we have a circle centered at (x1, y1)
and we want to move its center to the origin (0, 0)
to make math easier (simplify equations).

----------------------------------------------------
1️⃣ When shifting TO ORIGIN:
We subtract the circle’s center from every point:
    x' = x - x1
    y' = y - y1

Now the circle equation becomes:
    x'^2 + y'^2 = r^2
which means the circle is centered at (0, 0) now.

----------------------------------------------------
2️⃣ When shifting BACK to REAL COORDINATES:
After finding intersection or tangent points (x', y') 
in the shifted coordinate system,
we need to convert them back to original coordinates by:
    x = x' + x1
    y = y' + y1

----------------------------------------------------
🧩 Intuition:
Think of it as "picking up" the circle and moving it so 
its center sits at (0, 0). All points move by the same offset.
When we finish the math, we "move it back" by adding (x1, y1).

✅ Final rule:
If we shifted circle center to (0,0) from (x1,y1),
then to get any computed point back to real coordinates:
    (x, y) = (x' + x1, y' + y1)
*/



// ***************************************** circle centered origin *****************************************
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    double r, a, b, c;
    cin >> r >> a >> b >> c;

    // Step 1: Foot of perpendicular from circle center (origin) to line
    // Derived using projection formula: (x0, y0) = -(c / (a^2 + b^2)) * (a, b)
    double x0 = -a * c / (a * a + b * b);
    double y0 = -b * c / (a * a + b * b);

    // Distance squared from origin to the line: d^2 = c^2 / (a^2 + b^2)
    double distanceSquared = c * c / (a * a + b * b);

    // Step 2: Compare distance with radius
    if (c * c > r * r * (a * a + b * b) + EPS) {
        // If d > r → line lies outside the circle
        cout << "No intersection points\n";
    } 
    else if (fabs(c * c - r * r * (a * a + b * b)) < EPS) {
        // If d == r → line is tangent to the circle (touches at one point)
        cout << "One intersection point (tangent):\n";
        cout << fixed << setprecision(6) << x0 << " " << y0 << "\n";
    } 
    else {
        // Step 3: Line cuts the circle in two points (d < r)

        // Distance from the perpendicular foot to intersection along the line:
        // t = sqrt(r^2 - d^2)
        double offset = sqrt(r * r - distanceSquared);

        // Convert offset to scale along direction (b, -a)
        double mult = offset / sqrt(a * a + b * b);

        // Two intersection points found by moving along ±(b, -a)
        double x1 = x0 + b * mult;
        double y1 = y0 - a * mult;
        double x2 = x0 - b * mult;
        double y2 = y0 + a * mult;

        cout << "Two intersection points:\n";
        cout << fixed << setprecision(6);
        cout << x1 << " " << y1 << "\n" << x2 << " " << y2 << "\n";
    }

    return 0;
}
// ***************************************** circle centered origin *****************************************












// ***************************************** circle centered on (x1,y1) *****************************************
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    double x1, y1, r;  // Circle center (x1, y1) and radius r
    double a, b, c;    // Line: a·x + b·y + c = 0
    cin >> x1 >> y1 >> r >> a >> b >> c;

    /*
    🧠 Problem:
    We have a circle centered at (x1, y1) with radius r
    and a line: a·x + b·y + c = 0
    We must find intersection points.

    ✨ Trick:
    To simplify math, we "move" the circle center to (0,0)
    by translating the coordinate system.

    If we shift all points by (-x1, -y1),
    the line becomes: a·(x'+x1) + b·(y'+y1) + c = 0
    => a·x' + b·y' + (a·x1 + b·y1 + c) = 0
    So new constant term:
        c' = a·x1 + b·y1 + c
    */

    double cShifted = a * x1 + b * y1 + c;

    // Step 1️⃣: Find the foot of perpendicular from (0,0) to shifted line
    double x0 = -a * cShifted / (a * a + b * b);
    double y0 = -b * cShifted / (a * a + b * b);

    // Step 2️⃣: Distance squared from circle center (now at origin)
    double distanceSquared = cShifted * cShifted / (a * a + b * b);

    // Step 3️⃣: Compare distance with radius
    if (cShifted * cShifted > r * r * (a * a + b * b) + EPS) {
        cout << "No intersection points\n";
    }
    else if (fabs(cShifted * cShifted - r * r * (a * a + b * b)) < EPS) {
        cout << "One intersection point (tangent):\n";

        // Shift back to real coordinates
        cout << fixed << setprecision(6)
             << x0 + x1 << " " << y0 + y1 << "\n";
    }
    else {
        // Step 4️⃣: Distance from perpendicular foot to intersection
        double offset = sqrt(r * r - distanceSquared);

        // Step 5️⃣: Direction along the line = (b, -a)
        double mult = offset / sqrt(a * a + b * b);

        // Step 6️⃣: Two intersection points in shifted coordinates
        double x1p = x0 + b * mult;
        double y1p = y0 - a * mult;
        double x2p = x0 - b * mult;
        double y2p = y0 + a * mult;

        // Step 7️⃣: Shift back to real coordinates (+x1, +y1)
        cout << "Two intersection points:\n";
        cout << fixed << setprecision(6);
        cout << x1p + x1 << " " << y1p + y1 << "\n";
        cout << x2p + x1 << " " << y2p + y1 << "\n";
    }

    /*
    🧩 Summary:
    - We temporarily "move" the circle so its center is at origin.
    - We adjust the line constant: c' = a·x1 + b·y1 + c
    - Solve intersection for origin-centered circle.
    - Then "move back" the result by adding (x1, y1).

    This geometric translation keeps formulas simple and stable.
    */

    return 0;
}
// ***************************************** circle centered on (x1,y1) *****************************************
