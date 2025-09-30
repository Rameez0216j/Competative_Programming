#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a = 48, b = 18;

    cout << gcd(a, b) << "\n"; // 6

    long long x = 123456789012345, y = 98765432109876;
    cout << gcd(x, y) << "\n";   // works for long long too
    cout << lcm(12, 18) << "\n"; // 36

    return 0;
}
