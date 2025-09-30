#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    cin >> str;

    int n=str.size();

    if(n==0) return 0;
    
    int ans=1;
    int count=1;
    for (int i = 1; i < n; i++) {
        if(str[i]==str[i-1]) count++;
        else count=1;
        
        ans=max(ans,count);
    }

    cout<<ans<<"\n";
    return 0;
}
