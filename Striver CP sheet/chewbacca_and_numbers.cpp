#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    cin >> str;

    for (int i = 0; i < (int)str.size(); i++) {
        int d = str[i] - '0';
        int nd = 9 - d;              // inverted digit
        if (i == 0 && nd == 0) continue; // avoid leading zero
        if (nd < d) str[i] = '0' + nd;   // take the smaller option
    }

    cout << str << "\n";
    return 0;
}
