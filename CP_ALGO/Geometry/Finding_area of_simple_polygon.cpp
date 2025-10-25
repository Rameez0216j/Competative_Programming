//  See formula in CP ALgo page

#include <bits/stdc++.h>
using namespace std;

// 2D point structure
struct point {
    double x, y;
};

/*
    Polygon Area using Shoelace Formula

    Given a polygon with vertices in order: p0, p1, ..., p(n-1)
    (clockwise or counterclockwise), the area is calculated as:

        Area = 1/2 * | Σ (x_prev - x_curr) * (y_prev + y_curr) |

    where:
        - x_prev, y_prev = coordinates of previous vertex
        - x_curr, y_curr = coordinates of current vertex
        - The first vertex wraps around using modulo n (previous of p0 is p(n-1))

    Edge contribution:
        Each edge (p_prev -> p_curr) contributes:
            (x_prev - x_curr) * (y_prev + y_curr) / 2

    Notes:
        - Works for any simple polygon (convex or concave)
        - The sign of the sum indicates orientation:
            Positive  → Clockwise
            Negative  → Counterclockwise
        - Always take absolute value to get the positive area

    Example:

        Polygon vertices: (0,0), (4,0), (4,3), (0,3)
        Edges: (0,0)-(4,0), (4,0)-(4,3), (4,3)-(0,3), (0,3)-(0,0)

        Calculation:
            res = (0-4)*(0+0) + (4-4)*(0+3) + (4-0)*(3+3) + (0-0)*(3+0) = 24
            Area = |24| / 2 = 12
*/

double area(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        // Previous point (wraps around: last point before first)
        point p = i ? fig[i - 1] : fig.back();
        // Current point
        point q = fig[i];
        // Shoelace sum: (x_prev - x_curr) * (y_prev + y_curr)
        res += (p.x - q.x) * (p.y + q.y);
    }
    // Divide by 2 and take absolute value to get positive area
    return fabs(res) / 2;
}

int main() {
    vector<point> polygon = {{0,0}, {4,0}, {4,3}, {0,3}};
    cout << "Area of polygon: " << area(polygon) << endl; // Output: 12
}
