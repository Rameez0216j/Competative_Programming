#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s1="Rameez",s2="ahmad";
    auto it=remove(s1.begin(),s1.end(),'R');// Removes the given things and put last character to the last ex; removes R from Rameez and puts z at last as ameezz
    // This is to fill space occupied by string itself as removal of any character vacant the space which in turn filled by last character or iterator pointing to last in syntax and thus space is filled completely


    // for s2 output is hmd + ad from ahmad
    auto it1=remove(s2.begin(),s2.end(),'a');
    // remove(s3.begin(),s3.end(),'\r');
    cout<<*(it-2)<<" "<<*(it-1)<<" "<<*(it)<<endl;
    cout<<(*it1)<<endl;
    cout<<s1<<s2<<endl;
    return 0;
}