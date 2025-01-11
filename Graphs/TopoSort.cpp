#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph
{
    public:
    unordered_map<T, list<T>> adjList;

    void addEdge(T u, T v, bool direction)
    {
        // direction = 0 -> undirected graph
        // direction = 1 -> directed graph
        // create an edge from u to v
        adjList[u].push_back(v);
        if (direction == 0)
        {
            // undirected edge
            // create an edge from v to u
            adjList[v].push_back(u);
        }
    }

    void printAdjacencyList()
    {
        for (auto node : adjList)
        {
            cout << node.first << "-> ";
            for (auto neighbour : node.second)
            {
                cout << neighbour << ", ";
            }
            cout << endl;
        }
    }

    void topoSortDfs(int src, unordered_map<int, bool> &visited, stack<int> &ans)
    {

        visited[src] = true;

        for (auto neighbour : adjList[src])
        {
            if (!visited[neighbour])
            {
                topoSortDfs(neighbour, visited, ans);
            }
        }

        // while returning, store the node in stack
        ans.push(src);
    }

    // kahn's algorithm
    void topoSortBfs(int n, vector<int> &ans)
    {
        queue<int> q;
        unordered_map<int, int> indegree;

        // indegree calculate
        for (auto i : adjList)
        {
            int src = i.first;
            for (auto nbr : i.second)
            {
                indegree[nbr]++;
            }
        }

        // put all nodes inside queue, which has indegree=0
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // bfs logic
        while (!q.empty())
        {
            int fNode = q.front();
            q.pop();

            ans.push_back(fNode);
            // or we can do count++

            for (auto nbr : adjList[fNode])
            {
                indegree[nbr]--;
                // check for zero again
                if (indegree[nbr] == 0)
                {
                    q.push(nbr);
                }
            }
        }
    }
};