#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        arr.push_back(num);
    }

    long long int ans = 0;
    for (int i = 1; i < n; i++)
    {
        int num1 = arr[i - 1];
        int num2 = arr[i];

        if (num1 <= num2)
            continue;
        else{
            ans += (num1 - num2);
            arr[i] = arr[i - 1];
        }
    }

    cout << ans << "\n";
    return 0;
}