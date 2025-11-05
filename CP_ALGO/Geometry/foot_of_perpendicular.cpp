/*
🟢 Mathematical Intuition: Foot of Perpendicular from a Point to a Line

Given a line:
    a*x + b*y + c = 0

and a point:
    P(x1, y1)

We want the foot of the perpendicular:
    Q(x0, y0)

--------------------------------------------
Step 1️⃣: Equation of the line
    Since Q lies on the line:
        a*x0 + b*y0 + c = 0      ...(1)

Step 2️⃣: Perpendicular condition
    The normal vector of the line is (a, b).
    The vector PQ = (x0 - x1, y0 - y1) is parallel to (a, b).

    ⇒ PQ = k*(a, b)
       x0 = x1 + k*a
       y0 = y1 + k*b              ...(2)

Step 3️⃣: Substitute (2) into (1)
    a*(x1 + k*a) + b*(y1 + k*b) + c = 0
    ⇒ a*x1 + b*y1 + c + k*(a^2 + b^2) = 0
    ⇒ k = -(a*x1 + b*y1 + c) / (a^2 + b^2)

Step 4️⃣: Substitute back into (2)
    x0 = x1 - a*(a*x1 + b*y1 + c)/(a^2 + b^2)
    y0 = y1 - b*(a*x1 + b*y1 + c)/(a^2 + b^2)

✅ Therefore, the foot of the perpendicular is:
    Q(x0, y0) = (
        x1 - a*(a*x1 + b*y1 + c)/(a^2 + b^2),
        y1 - b*(a*x1 + b*y1 + c)/(a^2 + b^2)
    )

--------------------------------------------
⭐ Special Case: If the point is the origin (x1 = 0, y1 = 0)
    x0 = -a*c / (a^2 + b^2)
    y0 = -b*c / (a^2 + b^2)

--------------------------------------------
📏 Distance from the point (x1, y1) to the line:
    D = |a*x1 + b*y1 + c| / sqrt(a^2 + b^2)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    double a, b, c;  // line: a*x + b*y + c = 0
    double x1, y1;   // point P(x1, y1)
    cin >> a >> b >> c >> x1 >> y1;

    // Compute foot of perpendicular (x0, y0)
    double x0 = x1 - a * (a * x1 + b * y1 + c) / (a * a + b * b);
    double y0 = y1 - b * (a * x1 + b * y1 + c) / (a * a + b * b);

    cout << fixed << setprecision(6);
    cout << "Foot of perpendicular: (" << x0 << ", " << y0 << ")\n";

    // Compute perpendicular distance for verification
    double distance = fabs(a * x1 + b * y1 + c) / sqrt(a * a + b * b);
    cout << "Perpendicular distance: " << distance << "\n";

    return 0;
}