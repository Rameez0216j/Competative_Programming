#include<bits/stdc++.h>
using namespace std;


class Graph {
    public:
    unordered_map<int, list<pair<int,int>> > adjList;
    
    void ShortestPathBFS(int src, int dest) {
        queue<int> q;
        unordered_map<int,bool> visited;
        unordered_map<int,int> parent;

        //inital steps for src
        q.push(src);
        visited[src] = true;
        parent[src] = -1;

        while(!q.empty()) {
            int curr = q.front();
            q.pop();

            for(auto nbr: adjList[curr]) {
                if(!visited[nbr.first]) {
                    q.push(nbr.first);
                    visited[nbr.first] = true;
                    parent[nbr.first] = curr;
                }
            }
        }

        //store path in ans, after traversing in the parent array
        vector<int> ans;
        int node = dest;
        while(node != -1) {
            ans.push_back(node);
            node = parent[node];
        }

        reverse(ans.begin(), ans.end());

        cout << "printing ANs: " << endl;
        for(auto i: ans) {
            cout << i<<", ";
        }
        cout << endl;
        
    }


    void ShortestPathDFS(int dest, stack<int> topoOrder, int n) {
        // DFS is used in topoSort
        vector<int> dist(n, INT_MAX);
        int src = topoOrder.top();
        topoOrder.pop(); 
        dist[src] = 0;


        for(auto nbr: adjList[0]) {
            if(dist[0] + nbr.second < dist[nbr.first]) {
                dist[nbr.first] = dist[0] + nbr.second;
            }
        }
            

        while(!topoOrder.empty()) {
            int topElement = topoOrder.top();
            topoOrder.pop();

            if(dist[topElement] != INT_MAX) {
                for(auto nbr: adjList[topElement]) {
                    if(dist[topElement] + nbr.second < dist[nbr.first]) {
                        dist[nbr.first] = dist[topElement] + nbr.second;
                    }
                }
            }
        }

        cout << "Printing Ans: " << endl;
        for(int i=0; i<n; i++) {
            cout << i <<"-> " << dist[i] << endl;
        }
        
        
    }
};