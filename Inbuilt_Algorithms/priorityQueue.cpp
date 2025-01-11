#include<bits/stdc++.h>
using namespace std;

class comp2{
    public:
    bool operator()(pair<int,int> &a,pair<int,int> &b){
        return a.first > b.first;
    }

    // use below static comp if the function is in queue is defined in this class itself
    /*
        bool static operator()(pair<int,int> &a,pair<int,int> &b){
            return a.first > b.first;
        }
    */
};


struct comp3{
    bool operator()(pair<int,int> &a,pair<int,int> &b){
        return a.first > b.first;
    }
};


int main(){
    /*
        If priority queue is represented as vector then the item at the last index is at top priority
        So the comparator function of priority_queue is opposite to sorting comparator
    */

    // Method 1
    // Below comparator says that for order a,b  leave it as it is if a.first>b.first else swap and make b,a so that b.first>a.first 
    auto comp1=[](pair<int,int> &a,pair<int,int> &b){
        return a.first > b.first;
    };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(comp1)> pq1;

    // Method 2
    priority_queue<pair<int,int>,vector<pair<int,int>>,comp2> pq2;
    
    // Method 3
    priority_queue<pair<int,int>,vector<pair<int,int>>,comp3> pq3;

    return 0;
}


/*
    Key Points
        Method 1 uses a lambda expression, which works perfectly as a comparator.
        Method 2 uses a class-based comparator, and you can also remove the static keyword if desired (it works with or without).
        Method 3 uses a struct-based comparator, which also works well for priority queues.

*/