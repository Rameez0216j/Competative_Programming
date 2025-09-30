double ternarySearch(double l, double r) {
    while (r - l > 1e-6) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if (f(mid1) < f(mid2)) l = mid1;
        else r = mid2;
    }
    return f(l);  // or return l if index needed
}



/*
    🧠 Pattern:
    Used when: You are searching for the maximum or minimum value of a unimodal function

    Example problem: Finding the maximum value of a function within a range.

    Time: O(log(n))
    Space: O(1)


    ✅ Use in:

    Maximize area/volume/speed problems
    Minimize cost/time/effort problems
    Optimization problems
    Finding the maximum or minimum of a unimodal function
    Finding the maximum or minimum of a convex function
    Finding the maximum or minimum of a concave function
    Finding the maximum or minimum of a piecewise linear function
    Finding the maximum or minimum of a piecewise constant function
    Finding the maximum or minimum of a piecewise quadratic functionGeometric optimization
*/

