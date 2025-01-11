#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a=6,b=5;
    cout<<pow(a,b)<<endl;
    cout<<sqrt(a)<<endl;
    cout<<cbrt(a)<<endl;
    cout<<min(a,b)<<endl;
    cout<<min(a,b)<<endl;
    cout<<max(a,b)<<endl;
    cout<<max(a,b)<<endl;

    cout<<"Before swapping :"<<"a="<<a<<",b="<<b<<endl;
    // cout<<swap(a,b)<<endl; wrong
    swap(a,b);
    cout<<"After swapping :"<<"a="<<a<<",b="<<b<<endl;


    cout<<__gcd(a,b)<<endl;
    cout<<toupper('r')<<endl;
    cout<<tolower('R')<<endl;
    cout<<(char)toupper('r')<<endl;
    cout<<(char)tolower('R')<<endl;
    cout<<floor(2.7)<<endl;
    cout<<ceil(2.1)<<endl;
    return 0;
}