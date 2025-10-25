struct pt {
    double x, y;
};

struct line {
    double a, b, c; // a*x + b*y + c = 0

    // Construct line from two points
    line(const pt &p1, const pt &p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -(a * p1.x + b * p1.y);
    }

    

    // Normalize line (optional)
    void normalize() {
        double scale = sqrt(a*a + b*b);
        if(scale > 1e-9) {
            a /= scale;
            b /= scale;
            c /= scale;
        }
    }
};


/*
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = -(a * p1.x + b * p1.y);

    As slope =  -a/b = (p2.y - p1.y) /  (p2.x - p1.x)
*/