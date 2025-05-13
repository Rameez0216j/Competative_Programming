// 827. Making A Large Island --> Leetcode

#include <bits/stdc++.h>
using namespace std;

// *************** Union Find [Grid version - cells=node] - Solution 2 (Editorial) ***************
class Solution {
    public:
    int findParent(int node,vector<int> &parent){
        if(parent[node]!=node){
            parent[node]=findParent(parent[node],parent);
        }
        return parent[node];
    }

    int largestIsland(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();

        // n*m --> total no of nodes (considering each cell as a node)
        vector<int> parent(n*m,0);
        for(int i=0;i<n*m;i++) parent[i]=i; // Parent Initialization
        vector<int> rank(n*m,1); 

        // Unioin Find
        for(int row=0;row<n;row++){
            for(int col=0;col<m;col++){
                if(grid[row][col]==1){
                    vector<int> r={0,-1,0,1};
                    vector<int> c={-1,0,1,0};
                    int curr=n*row+col;
                    for(int i=0;i<4;i++){
                        int new_row=row+r[i];
                        int new_col=col+c[i];

                        if(new_row>=0 && new_row<n && new_col>=0 && new_col<m && grid[new_row][new_col]==1){
                            int nbr=n*new_row+new_col;
                            int parent_curr=findParent(curr,parent);
                            int parent_nbr=findParent(nbr,parent);

                            if(parent_curr == parent_nbr) continue;

                            if(rank[parent_curr] > rank[parent_nbr]){
                                parent[parent_nbr]=parent_curr;
                                rank[parent_curr]+=rank[parent_nbr];
                            }else{
                                parent[parent_curr]=parent_nbr;
                                rank[parent_nbr]+=rank[parent_curr];
                            }
                        } 
                    }
                }
            }
        }


        // Now finding top 2 parent with highest rank and adding them to return
        int ans=*max_element(rank.begin(),rank.end());
        for(int row=0;row<n;row++){
            for(int col=0;col<m;col++){
                if(grid[row][col]==0){
                    vector<int> r={0,-1,0,1};
                    vector<int> c={-1,0,1,0};

                    int total_land=1;
                    set<int> nbr_parents;
                    for(int i=0;i<4;i++){
                        int new_row=row+r[i];
                        int new_col=col+c[i];
                        if(new_row>=0 && new_row<n && new_col>=0 && new_col<m && grid[new_row][new_col]==1){
                            int nbr=new_row*n+new_col;
                            int nbr_parent=findParent(nbr,parent);
                            if(nbr_parents.find(parent[nbr])==nbr_parents.end()){
                                total_land+=rank[nbr_parent];
                                nbr_parents.insert(nbr_parent);
                            }
                        }
                    }
                    nbr_parents.clear();
                    ans=max(ans,total_land);
                }
            }
        }

        return ans;
    }
};
// *************** Union Find [Grid version - cells=node] - Solution 2 (Editorial) ***************
