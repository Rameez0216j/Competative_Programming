#include<bits/stdc++.h>
using namespace std;


class graph {
    public:
    unordered_map<int, list<pair<int,int>> > adjList;
    void bellmanFordAlgo(int n, int src) {
        //assuming directed weightted graph
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        //n-1 relaxation step
        for(int i=0; i<n-1; i++) {
            //for all edges
            for(auto t: adjList) {
                for(auto nbr: t.second) {
                    int u = t.first;
                    int v = nbr.first;
                    int wt = nbr.second;
                    if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                        dist[v] = dist[u] + wt;
                    }
                }
            }
        }

        //To check for -ve cycle
        bool negativeCycle = false;
        for(auto t: adjList) {
            for(auto nbr: t.second) {
                int u = t.first;
                int v = nbr.first;
                int wt = nbr.second;
                if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                    negativeCycle = true;
                    break;
                }
            }
        }

        if(negativeCycle == true) cout << "-ve cycle present";
        else cout << "-ve cycle absent";

        cout << "printing Dist array (Shortest distance from the source node to every other node in the graph) : ";
        for(auto i : dist) cout << i << " ";
    }
};