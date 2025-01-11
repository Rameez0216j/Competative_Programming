#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> v;
    int n;
    cin>>n;
    cout<<"Enter Vector elements : ";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    //episode 36
    // passed iterators as start and end can be manipulated in below syntax
    auto it=min_element(v.begin(),v.end());
    auto it1=max_element(v.begin(),v.end());
    int sum=accumulate(v.begin(),v.end(),0); // 0 is initial sum to which sum of vector elements is to be added
    int ct=count(v.begin(),v.end(),6);// 6 ---> element whose count is to be determined
    auto it2=find(v.begin(),v.end(),6); // returns same element if found else last+1 address (invalid) [use if statements to avoid abnormality]
    cout<<(*it)<<" "<<(*it1)<<" "<<sum<<" "<<ct<<" "<<(*it2)<<endl;

    // reversing array/vector
    reverse(v.begin(),v.end()); //now simply print vector and see it is reversed
    cout<<"Vector elements are: ";
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    // Reversing string
    string s="Rameez Ahmad";
    reverse(s.begin(),s.end());
    cout<<s<<endl;



    // NOTE : all iterators,locations,pointers used above can be manipulated as ptr+n,ptr++ etc.....
    // also v.begin()+n,v.end()+n where n ---> integer(any)
    // arrays can use (a,a+n) for above operations
    // all above operations are of O(n)

    return 0;
}