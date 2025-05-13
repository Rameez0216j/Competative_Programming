// 3302.Find_Minimum_Diameter_After_Merging_Two Trees
/*
    This is all you need, and you will solve this question smoothly 😁

    Input : 
        edges1 = [[0,1],[2,0],[3,2],[3,6],[8,7],[4,8],[5,4],[3,5],[3,9]]
        edges2 = [[0,1],[0,2],[0,3]]
    Output : 6
    Expected : 7
    
    Explaination : 
    MaxReach here represents the longest path in the tree from the current node : "node" --> longest path from "node" internally
    MaxReach in Tree1 : 0-->6, 2-->5, 3-->4, 9-->5, 5-->4, 4-->5, 8-->6, 7-->7, 6-->5, 1-->7
    MaxReach in Tree2 : 0-->1, 3-->2, 2-->2, 1-->2
    Look if we want to join them with minimum diameter we do mergedDiameter=min(maxReaxh1)+min(maxReach2)+1
    but internal diameter of Tree1 = 7 > mergedDiameter
    and inernal diameter of Tree2 = 2 < mergedDiameter

    So answer should be --> ans = max(mergedDiameter,internalDiameter1,internalDiameter2);
*/


// ******************************** My Solution ********************************
class Solution {
    public:
    /*
    */
    int findMaxReach(int root,int parent,int maxiTowardsParent,unordered_map<int,int> &tracker,unordered_map<int,int> &maxReach,unordered_map<int,vector<int>> &adjM){
        int maxi=0;
        // Store the current maxReach from parent
        tracker[root]=maxiTowardsParent;
        // find the maxReach from currNode to all its child nodes and store in maxi;
        for(int nbr:adjM[root]){
            if(nbr==parent) continue;
            maxi=max(maxi,findMaxReach(nbr,root,tracker[root]+1,tracker,maxReach,adjM));
            tracker[root]=max(maxi,tracker[root]);
        }
        // update the actual maxReach with maxReach from parent and child
        maxReach[root]=max(maxReach[root],tracker[root]);
        return maxi+1;
    }

    pair<int,int> miniReach(unordered_map<int,int> &maxReach){
        int mini=INT_MAX;
        int maxi=INT_MIN;
        for(auto ele:maxReach){
            mini=min(mini,ele.second);
            maxi=max(maxi,ele.second);
        }
        return {mini,maxi};
    }

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int ans=0;
        
        unordered_map<int,int> maxReach1;
        unordered_map<int,int> tracker1;
        unordered_map<int,vector<int>> adjM1;
        for(auto edge : edges1){
            int u=edge[0];
            int v=edge[1];
            adjM1[u].push_back(v);
            adjM1[v].push_back(u);
        }
        
        findMaxReach(0,-1,0,tracker1,maxReach1,adjM1);
        tracker1.clear();
        for(auto &nbrs:adjM1) reverse(nbrs.second.begin(),nbrs.second.end());
        findMaxReach(0,-1,0,tracker1,maxReach1,adjM1);
        // for(auto val:maxReach1) cout<<val.first<<"-->"<<val.second<<",";
        // cout<<endl;


        unordered_map<int,int> maxReach2;
        unordered_map<int,int> tracker2;
        unordered_map<int,vector<int>> adjM2;
        for(auto edge : edges2){
            int u=edge[0];
            int v=edge[1];
            adjM2[u].push_back(v);
            adjM2[v].push_back(u);
        }
        findMaxReach(0,-1,0,tracker2,maxReach2,adjM2);
        tracker2.clear();
        for(auto &nbrs:adjM2) reverse(nbrs.second.begin(),nbrs.second.end());
        findMaxReach(0,-1,0,tracker2,maxReach2,adjM2);
        // for(auto val:maxReach2) cout<<val.first<<"-->"<<val.second<<",";
        // cout<<endl;


        auto [miniReach1,internalDiameter1]=miniReach(maxReach1);
        auto [miniReach2,internalDiameter2]=miniReach(maxReach2);
        return max(miniReach1+miniReach2+1 , max(internalDiameter1 , internalDiameter2));

        // cout<<miniReach1<<"|"<<miniReach2<<endl;
        // return 1;
    }
};
// ******************************** My Solution ********************************
