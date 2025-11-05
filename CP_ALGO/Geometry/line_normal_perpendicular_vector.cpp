/*
🟢 Mathematical Note: Perpendicular Vector to (a, b)

Let’s say we have a vector:
    v = (a, b)

We want to find another vector that is **perpendicular** to it.

----------------------------------------------------------
📘 Condition for Perpendicularity:
Two vectors (u1, u2) and (v1, v2) are perpendicular if:
    u1*v1 + u2*v2 = 0     ← (dot product = 0)

----------------------------------------------------------
Let’s find a perpendicular vector (x, y) for (a, b):

    a*x + b*y = 0

Pick:
    x = -b
    y = a

Then:
    a*(-b) + b*(a) = -ab + ab = 0 ✅

Hence, (-b, a) is perpendicular to (a, b).

----------------------------------------------------------
Alternatively:
Pick:
    x = b
    y = -a

Then:
    a*(b) + b*(-a) = ab - ab = 0 ✅

So (b, -a) is also perpendicular to (a, b).

----------------------------------------------------------
🧭 Summary:
If (a, b) is the line’s **normal vector**,
then the line’s **direction vector** (tangent) is:

    → (-b, a)  or  (b, -a)

Both are correct — they just point in opposite directions.

----------------------------------------------------------
Example:
Line:  3x + 4y + 5 = 0
Normal vector  = (3, 4)
Direction vector = (-4, 3) or (4, -3)
*/
