#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    // Sort points by x, break ties with y
    bool operator < (Point P) const {
        if (x == P.x) return y < P.y;
        else return x < P.x;
    }

    // Equality check
    bool operator == (Point P) const {
        return (x == P.x && y == P.y);
    }
};

// Returns true if three points make a clockwise turn
bool cw(Point a, Point b, Point c) {
    return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) > 0;
}

// Returns true if three points make a counter-clockwise turn
bool ccw(Point a, Point b, Point c) {
    return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) < 0;
}

// Returns true if three points are collinear
bool cll(Point a, Point b, Point c) {
    return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) == 0;
}

// Convex Hull using Monotone Chain
vector<Point> convex_hull(vector<Point> points) {
    if (points.size() <= 2) return points; // Hull is trivial

    // Sort points lexicographically (by x then y)
    sort(points.begin(), points.end());

    vector<Point> up, down;
    Point first = points[0], last = points.back();

    up.push_back(first);
    down.push_back(first);

    for (int i = 1; i < points.size(); i++) {
        // Build upper hull
        if (i == points.size() - 1 || cw(first, points[i], last)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], points[i])) {
                up.pop_back(); // Remove points making non-clockwise turn
            }
            up.push_back(points[i]);
        }

        // Build lower hull
        if (i == points.size() - 1 || ccw(first, points[i], last)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], points[i])) {
                down.pop_back(); // Remove points making non-counter-clockwise turn
            }
            down.push_back(points[i]);
        }
    }

    // Combine upper and lower hulls
    points.clear();
    for (auto p : up) points.push_back(p);
    for (auto p : down) points.push_back(p);

    // Remove duplicates
    sort(points.begin(), points.end());
    points.resize(unique(points.begin(), points.end()) - points.begin());

    return points;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convex_hull(points);

    for (auto x : hull) {
        cout << x.x << " " << x.y << '\n';
    }

    return 0;
}








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