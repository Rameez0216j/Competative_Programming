// Solution : https://www.youtube.com/watch?v=QyrmIu4Vo8A
// This can also be solve dusing Khan's Algorithm for Topo Sort
// ************************************* My Solution *************************************
class Solution {
    int InvalidConditions=false;

    public:
    void topoSort(int node,vector<bool> &visited,vector<bool> &topoVisited,unordered_map<int,vector<int>> &adjL,stack<int> &topoOrder){
        // Stop if already Invalid conditions met 
        if(InvalidConditions) return;

        visited[node]=true;
        topoVisited[node]=true;

        for(auto nbr: adjL[node]){
            if(topoVisited[nbr]){
                InvalidConditions=true; // cycle exist (invalid conditions)
                return;
            }
            else if(!visited[nbr]) topoSort(nbr,visited,topoVisited,adjL,topoOrder);
        }

        topoVisited[node]=false;
        topoOrder.push(node);
    }

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        int n=rowConditions.size();
        int m=colConditions.size();

        vector<int> rowOrder(k,-1);
        vector<int> colOrder(k,-1);

        unordered_map<int,vector<int>> rowAdjL,colAdjL;
        for(int i=0;i<n;i++){
            int u=rowConditions[i][0]-1;
            int v=rowConditions[i][1]-1;
            rowAdjL[u].push_back(v);
        }

        for(int i=0;i<m;i++){
            int u=colConditions[i][0]-1;
            int v=colConditions[i][1]-1;
            colAdjL[u].push_back(v);
        }


        stack<int> rowTopoOrder,colTopoOrder;
        vector<bool> rowVisited(k,false);
        vector<bool> colVisited(k,false);
        vector<bool> topoVisited(k,false); // this will reset to false after every topo call
        for(int i=0;i<k;i++){
            if(!rowVisited[i]){
                topoSort(i,rowVisited,topoVisited,rowAdjL,rowTopoOrder);
            }

            if(!colVisited[i]){
                topoSort(i,colVisited,topoVisited,colAdjL,colTopoOrder);
            }

            if(InvalidConditions) return {};
        }

        int rowNumber=0;
        while(!rowTopoOrder.empty()){
            int val=rowTopoOrder.top();
            rowTopoOrder.pop();

            if(rowOrder[val]!=-1) continue;
            rowOrder[val]=rowNumber;
            rowNumber++;
        }


        int colNumber=0;
        while(!colTopoOrder.empty()){
            int val=colTopoOrder.top();
            colTopoOrder.pop();

            if(colOrder[val]!=-1) continue;
            colOrder[val]=colNumber;
            colNumber++;
        }

        vector<vector<int>> ans(k,vector<int>(k,0));
        for(int i=0;i<k;i++){
            ans[rowOrder[i]][colOrder[i]]=i+1;
        }
        return ans;
    }
};
// ************************************* My Solution *************************************






// ************************************* My Solution [Cleaned] *************************************
/*
class Solution {
    bool hasCycle = false; // Flag to detect invalid conditions (cycle in graph)

public:
    // -----------------------------
    // Topological Sort using DFS
    // -----------------------------
    void topoSort(
        int node,
        vector<bool>& visited,
        vector<bool>& dfsVisited,
        unordered_map<int, vector<int>>& adjList,
        stack<int>& topoStack
    ) {
        // Stop immediately if a cycle is already detected
        if (hasCycle) return;

        visited[node] = true;
        dfsVisited[node] = true; // Mark node as part of current DFS path

        for (auto neighbor : adjList[node]) {
            if (dfsVisited[neighbor]) {
                // Cycle detected → invalid conditions
                hasCycle = true;
                return;
            }
            else if (!visited[neighbor]) {
                topoSort(neighbor, visited, dfsVisited, adjList, topoStack);
            }
        }

        dfsVisited[node] = false; // Backtrack: remove from current DFS path
        topoStack.push(node);      // Add node to topological order
    }

    vector<vector<int>> buildMatrix(
        int k,
        vector<vector<int>>& rowConditions,
        vector<vector<int>>& colConditions
    ) {
        // -----------------------------
        // Step 1: Initialize topological order containers
        // -----------------------------
        vector<int> rowPosition(k, -1); // row index of each number
        vector<int> colPosition(k, -1); // column index of each number

        unordered_map<int, vector<int>> rowAdjList, colAdjList;

        // Build adjacency list for row conditions
        for (auto& edge : rowConditions) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            rowAdjList[u].push_back(v);
        }

        // Build adjacency list for column conditions
        for (auto& edge : colConditions) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            colAdjList[u].push_back(v);
        }

        // -----------------------------
        // Step 2: Perform topological sort for rows and columns
        // -----------------------------
        stack<int> rowTopoStack, colTopoStack;
        vector<bool> rowVisited(k, false), colVisited(k, false);
        vector<bool> dfsVisited(k, false); // Tracks current DFS path

        for (int i = 0; i < k; i++) {
            if (!rowVisited[i]) topoSort(i, rowVisited, dfsVisited, rowAdjList, rowTopoStack);
            if (!colVisited[i]) topoSort(i, colVisited, dfsVisited, colAdjList, colTopoStack);

            if (hasCycle) return {}; // Impossible to satisfy conditions
        }

        // -----------------------------
        // Step 3: Assign row indices based on topological order
        // -----------------------------
        int rowNumber = 0;
        while (!rowTopoStack.empty()) {
            int val = rowTopoStack.top();
            rowTopoStack.pop();

            if (rowPosition[val] != -1) continue;
            rowPosition[val] = rowNumber++;
        }

        // -----------------------------
        // Step 4: Assign column indices based on topological order
        // -----------------------------
        int colNumber = 0;
        while (!colTopoStack.empty()) {
            int val = colTopoStack.top();
            colTopoStack.pop();

            if (colPosition[val] != -1) continue;
            colPosition[val] = colNumber++;
        }

        // -----------------------------
        // Step 5: Build final matrix using assigned row & column positions
        // -----------------------------
        vector<vector<int>> matrix(k, vector<int>(k, 0));
        for (int i = 0; i < k; i++) {
            matrix[rowPosition[i]][colPosition[i]] = i + 1;
        }

        return matrix;
    }
};
*/
// ************************************* My Solution [Cleaned] *************************************