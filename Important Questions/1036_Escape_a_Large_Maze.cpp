// NORMAL RECURSION CODE WILL GIVE TLE AND MEMOIZED CODE WILL GIVE MLE 


// Solution : https://www.youtube.com/watch?v=bZqIfxD902c
// ******************************************* My Solution *******************************************
class Solution {
    public:
    bool isValid(int next_row,int next_col){
        return (next_row < 1e6) && (next_col < 1e6) && (next_row >=0 ) && (next_col >=0 );
    }
    
    bool solveBFS(vector<int>& source, vector<int>& target,vector<vector<int>>& blocked){
        int n=blocked.size();
        int maxBlockableCells=(n*(n-1))/2;

        unordered_map<int,unordered_map<int,bool>> obstacles,visited;
        for(auto cell : blocked) obstacles[cell[0]][cell[1]]=true;

        queue<vector<int>> q;
        q.push(source);
        visited[source[0]][source[1]]=true;
        int count=1;
        while(!q.empty()){
            vector<int> curr=q.front();
            q.pop();

            if(curr[0]==target[0] && curr[1]==target[1]) return true;
            if(count > maxBlockableCells) return true; // now we are unstoppable (no blocks are able to block the path no matter where they are placed)

            vector<int> r={0,0,1,-1};
            vector<int> c={1,-1,0,0};

            for(int i=0;i<4;i++){
                int next_row=curr[0]+r[i];
                int next_col=curr[1]+c[i];

                if(isValid(next_row,next_col) && !obstacles[next_row][next_col] && !visited[next_row][next_col]){
                    visited[next_row][next_col]=true;
                    q.push({next_row,next_col});
                    count++;
                }
            }
        }

        // Not able to reach target nwither crossed maxBlockableCells
        return false;
    }

    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        return solveBFS(source,target,blocked) && solveBFS(target,source,blocked);
    }
};
// ******************************************* My Solution *******************************************