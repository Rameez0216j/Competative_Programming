#include <bits/stdc++.h>
using namespace std;


template <typename T>
class Graph{
    public:
    unordered_map<T, list<T>> adjList;
    bool CycleDetectionBFS(int src, unordered_map<int, bool> &visited){
        queue<int> q;
        unordered_map<int, int> parent;

        q.push(src);
        visited[src] = true;
        parent[src] = -1;

        while (!q.empty()){
            int frontNode = q.front();
            q.pop();

            for (auto nbr : adjList[frontNode]){
                if (!visited[nbr]){
                    q.push(nbr);
                    visited[nbr] = true;
                    parent[nbr] = frontNode;
                }

                if (visited[nbr] && nbr != parent[frontNode]){
                    // cycle present
                    return true;
                }
            }
        }
        return false;
    }


    bool CycleDetectionDFS(int src, unordered_map<int, bool> &visited, int parent){
        visited[src] = true;

        for (auto nbr : adjList[src]){
            if (!visited[nbr]){
                if(CycleDetectionDFS(nbr, visited, src)){
                    return true;
                }
            }else if (visited[nbr] && nbr != parent) return true; // cycle present
        }
        return false;
    }


    // Directed Graph
    bool CycleDetectionDFS_Directed(int src, unordered_map<int, bool> &visited, unordered_map<int, bool> &DFS_Visited){
        visited[src] = true;
        DFS_Visited[src] = true;

        for (auto nbr : adjList[src]){
            if (!visited[nbr]){
                bool aageKaAnswer = CycleDetectionDFS_Directed(nbr, visited, DFS_Visited);
                if (aageKaAnswer == true) return true;
            }else if (visited[nbr] == true && DFS_Visited[nbr] == true) return true;
        }
        // yaha hi galti hoti hai
        DFS_Visited[src] = false;
        return false;
    }
};
