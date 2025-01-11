#include<bits/stdc++.h>
using namespace std;


class Graph {
    public:
    unordered_map<int, list<pair<int,int>> > adjList;
    
    // Single Source Shortest Path
    void Dijkstra_set(int src, int n) {
        vector<int> dist(n,INT_MAX);
        set<pair<int,int> > st;
        //intiial steps
        dist[src] = 0;
        st.insert(make_pair(0,src));

        while(!st.empty()){
            //fetch the smallest or first eklement from set
            auto topElement = *(st.begin());
            int nodeDistance = topElement.first;
            int node = topElement.second;

            //pop from set
            st.erase(st.begin());

            //neighbour traverse
            for(auto nbr: adjList[node]) {
                if(nodeDistance + nbr.second < dist[nbr.first]) {
                    //mujhe distance update krna h
                    //finding entry in set
                    auto result = st.find(make_pair(dist[nbr.first], nbr.first));
                    //if found, then remove
                    if(result != st.end()) {
                        st.erase(result);
                    }
                    //updation in dist array and set
                    dist[nbr.first] = nodeDistance + nbr.second;
                    st.insert(make_pair(dist[nbr.first], nbr.first));
                }
            }
            
        }

        cout << "Printing ans : ";
        for(int i=0; i<n; i++) cout << dist[i] <<", ";
        cout << endl;
    }



    // Single Source Shortest Path
    void Dijkstra_pq(int src, int n) {
        vector<int> dist(n,INT_MAX);
        auto comp=[](pair<int,int> &a,pair<int,int> &b){
            return a.first > b.first;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(comp)> pq;
        //intiial steps
        dist[src] = 0;
        pq.push({0,src});

        while(!pq.empty()){
            auto [nodeDistance , node] = pq.top();
            pq.pop();

            //neighbour traverse
            for(auto nbr: adjList[node]) {
                if(nodeDistance + nbr.second < dist[nbr.first]) {
                    dist[nbr.first] = nodeDistance + nbr.second;
                    pq.push(make_pair(dist[nbr.first], nbr.first));
                }
            }
            
        }

        cout << "Printing ans : ";
        for(int i=0; i<n; i++) cout << dist[i] <<", ";
        cout << endl;
    }
};