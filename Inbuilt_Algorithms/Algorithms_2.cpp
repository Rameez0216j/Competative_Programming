#include <bits/stdc++.h>
using namespace std;
bool is_positive(int x){
    return x>0;
}
int main()
{
    //episode 37
    //All_of algorithms---> check a condition with all elements of a array and returns true if all elements satisfies the condition
    //Any_of algorithms---> check a condition with all elements of a array and returns true if at least one elements satisfies the condition
    //none_of algorithms---> check a condition with all elements of a array and returns true if none of the  elements satisfies the condition

    //lambda function
    //Syntax --> [](parameters list){return statement;}
    //_calling_syntax --> [](parameters list){return statement;}(arguments list)
    // EX:-[](int x){return x+2;}
    cout<<[](int x){return x+2;}(2)<<endl;
    auto sum=[](int x,int y){return x+y;};
    cout<<sum(2,3)<<endl;


    vector<int> v={4,5,6,7,8,9};
    // All_of function
    cout<<all_of(v.begin(),v.end(),[](int x){return x>0;})<<endl;
    cout<<all_of(v.begin(),v.end(),is_positive)<<endl;// similar to above function
    cout<<all_of(v.begin(),v.end(),[](int x){return x>7;})<<endl;


    //Any_of function
    cout<<any_of(v.begin(),v.end(),[](int x){return x>7;})<<endl;

    //None_of function
    cout<<none_of(v.begin(),v.end(),[](int x){return x>7;})<<endl;
    cout<<none_of(v.begin(),v.end(),[](int x){return x>10;})<<endl;

    // above functions can also be used with arrays as (a,a+n)
    // try using lambda functions they save a lot of time and become handy with time 
    return 0;
}