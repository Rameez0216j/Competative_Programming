// 684. Redundant Connection
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    int findParent(int node,vector<int> &parent){
        if(parent[node]!=node){
            parent[node]=findParent(parent[node],parent);
        }
        return parent[node];
    }

    void UnionFind(vector<vector<int>>& edges) {
        vector<int> ans;
        int n=edges.size(); // It is given size of edges is n and number of nodes is also n
        vector<int> parent(n,0);
        for(int i=0;i<n;i++) parent[i]=i;
        vector<int> rank(n,1);

        for(int i=0;i<n;i++){
            int u=edges[i][0]-1;
            int v=edges[i][1]-1;

            int parent_u=findParent(u,parent);
            int parent_v=findParent(v,parent);

            // Union Operation based on rank
            if(rank[parent_u] > rank[parent_v]){
                parent[parent_v]=parent_u;
                rank[parent_u]++;
            }else{
                parent[parent_u]=parent_v;
                rank[parent_v]++;
            }

            // Union Operation based on size (assume rank as size)
            /*
            if(rank[parent_u] > rank[parent_v]){
                parent[parent_v]=parent_u;
                rank[parent_u]+=rank[parent_v];
            }else{
                parent[parent_u]=parent_v;
                rank[parent_v]+=rank[parent_u];
            }
            */
        }

    }
};