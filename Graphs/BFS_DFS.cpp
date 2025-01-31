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

    void bfs(int src, unordered_map<int, bool> &visited)
    {
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {
            int frontNode = q.front();
            q.pop();
            cout << frontNode << ", ";

            // insert neighbours
            for (auto neighbour : adjList[frontNode])
            {
                if (!visited[neighbour])
                {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }


        void dfs(int src, unordered_map<int, bool> &visited)
        {
            cout << src << ", ";
            visited[src] = true;

            for (auto neighbour : adjList[src])
            {
                if (!visited[neighbour])
                {
                    dfs(neighbour, visited);
                }
            }
        }
    }
};
