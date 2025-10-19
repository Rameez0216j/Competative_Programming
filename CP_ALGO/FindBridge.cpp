#include <bits/stdc++.h>
using namespace std;

class graph
{
    public:
    unordered_map<int, list<int>> adjList;
    void findBridges(int src, int parent, int &timer, vector<int> &initial_time, vector<int> &lowest_time, unordered_map<int, bool> visited){
        visited[src] = true;
        initial_time[src] = timer;
        lowest_time[src] = timer;
        timer++;

        for (auto nbr : adjList[src]){
            if (nbr == parent) continue;
            if (!visited[nbr]){
                // DFS Call
                findBridges(nbr, src, timer, initial_time, lowest_time, visited);
                // lowest_time update
                lowest_time[src] = min(lowest_time[src], lowest_time[nbr]);
                // check for bridge
                if (lowest_time[nbr] > initial_time[src]){
                    cout << nbr << "--" << src << " is a bridge" << endl;
                }
            }
            else{
                // node is visitedited and not a parent
                // lowest_time update
                lowest_time[src] = min(lowest_time[src], lowest_time[nbr]);
            }
        }
    }
};
