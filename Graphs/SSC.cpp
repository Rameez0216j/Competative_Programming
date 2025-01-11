#include<bits/stdc++.h>
using namespace std;


class graph {
    public:
    unordered_map<int, list<int> > adjList;
    void TopoOrder(int src, stack<int>& s, unordered_map<int,bool>& vis) {
        vis[src] = true;

        for(auto nbr: adjList[src]) {
            if(!vis[nbr]) {
                TopoOrder(nbr, s, vis);
            }
        }
        s.push(src);
    }

    void DFS1(int src, unordered_map<int,bool>& visited, unordered_map<int,list<int> >& adjNew) {
        visited[src] = true;
        cout << src << ", ";

        for(auto nbr: adjNew[src]) {
            if(!visited[nbr] ) {
                DFS1(nbr, visited, adjNew);
            }
        }
    }

    int countSCC(int n) {
        stack<int> s;
        unordered_map<int,bool> visited;

        //find topo ordering
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                TopoOrder(i,s,visited);
            }
        }

        //reverse all edges
        unordered_map<int,list<int> > adjNew;
        
        for(auto t: adjList) {
            for(auto nbr: t.second) {
                int u = t.first;
                int v = nbr;
                //v-> u insert
                adjNew[v].push_back(u);
            }
        }

        //traversse using DFS1
        int count = 0;
        unordered_map<int,bool> visited2;

        while(!s.empty()) {
            int node = s.top();
            s.pop();
            if(!visited2[node]) {
                cout << "Printing "<< count+1 << "th SCC: ";
                DFS1(node,visited2, adjNew);
                cout << endl;
                count++;
            }
        }
        return count;
    }

    void DFS2(int src, unordered_map<int,bool>& visited, unordered_map<int,list<int> >& adjNew,vector<int> &SCC) {
        visited[src] = true;
        SCC.push_back(src);

        for(auto nbr: adjNew[src]) {
            if(!visited[nbr] ) {
                DFS2(nbr, visited, adjNew,SCC);
            }
        }
    }

    vector<vector<int>> FindSCC(int n) {
        stack<int> s;
        unordered_map<int,bool> visited;

        //find topo ordering
        for(int i=0; i<n; i++) {
            if(!visited[i]) {
                TopoOrder(i,s,visited);
            }
        }

        //reverse all edges
        unordered_map<int,list<int> > adjNew;
        
        for(auto t: adjList) {
            for(auto nbr: t.second) {
                int u = t.first;
                int v = nbr;
                //v-> u insert
                adjNew[v].push_back(u);
            }
        }

        //traversse using DFS1
        vector<vector<int>> SCCs;
        unordered_map<int,bool> visited2;

        while(!s.empty()) {
            int node = s.top();
            s.pop();
            if(!visited2[node]) {
                vector<int> SCC;
                DFS2(node,visited2, adjNew,SCC);
                SCCs.push_back(SCC);
            }
        }
        return SCCs;
    }

};
