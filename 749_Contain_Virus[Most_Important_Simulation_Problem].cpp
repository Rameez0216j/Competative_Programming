// ********************************* My Solution - [Simple Simulation] *********************************
/*
    Code:
    return a.wallsCount < b.wallsCount; ❌ — Wrong / Incorrect
    return a.neighbours.size() < b.neighbours.size(); ✅ — Right / Correct

    Reason:
    Consider,
    vector<vector<int>> isInfected = {
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 1},
            {1, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0}
        };

        In above example of 11*6 isInfected grid,
        R1 (circle) ==> wallsCount=9+4=13  neighbours.size()=10
        R2 (Line) ==> wallsCount=9+2=11  neighbours.size()=11 
*/

class Regeion{
    public:
    // all set,vector,unordered_set ==> iterable using for(auto ele: set,vector,unordered_set)
    set<pair<int,int>> contaminated;
    set<pair<int,int>> neighbours; // This will store the neighbouring cells (avoid saving again and again whenever entered from some other neighbour and thus keeping it unique and counting the wallsCounts from all neighbours entry as well)
    int wallsCount; // This will store walls against the neighbouring cells 
    Regeion() : wallsCount(0) {}
};


class Solution {
    public:
    void DFS(int row,int col,vector<vector<bool>> &visited,vector<vector<int>> &isInfected,Regeion &R){
        if(row<0 || col<0 || row>=isInfected.size() || col>=isInfected[0].size() || visited[row][col] || isInfected[row][col]==-1) return;
        if(isInfected[row][col]==0){
            R.neighbours.insert({row,col});
            R.wallsCount++;
            return;
        }

        visited[row][col]=true;
        R.contaminated.insert({row,col}); // as it is contaminated isInfected[row][col]==1
        int r[]={1,-1,0,0};
        int c[]={0,0,1,-1};
        for(int i=0;i<4;i++){
            int new_row=row+r[i];
            int new_col=col+c[i];
            DFS(new_row,new_col,visited,isInfected,R);
        }
    }

    int containVirus(vector<vector<int>>& isInfected) {
        int ans=0;
        int n=isInfected.size();
        int m=isInfected[0].size();

        auto comp=[](Regeion &a,Regeion &b){
            // return a.wallsCount < b.wallsCount; // This is wrong (Find Why ?)
            return a.neighbours.size() < b.neighbours.size(); // This is correct (our motive is to count which is effecting many neighbours cells not the number of walls)
        };
        priority_queue<Regeion,vector<Regeion>,decltype(comp)> pq;

        while(true){
            vector<vector<bool>> visited(n,vector<bool>(m,false));
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(isInfected[i][j]==1 && !visited[i][j]){
                        Regeion R; // Note:  Creates an object 'R' of class Regeion and calls Regeion's default constructor
                        DFS(i,j,visited,isInfected,R);
                        pq.push(R);
                    }
                }
            }

            
            if(pq.size()==0) break; // when all regeions are blocked from spread
            
 
            Regeion currDanger=pq.top();
            pq.pop();
            // Fence the currDanger Regeion
            for(auto indices: currDanger.contaminated){
                int row=indices.first;
                int col=indices.second;
                isInfected[row][col]=-1;
            }
            ans+=currDanger.wallsCount; // as these many walls are needed to block the spread

            
            // Simulate the spread
            while(!pq.empty()){
                Regeion leftover_Regeions=pq.top();
                pq.pop();

                for(auto indices: leftover_Regeions.neighbours){
                    int row=indices.first;
                    int col=indices.second;
                    isInfected[row][col]=1;
                }
            }
        }

        return ans;
    }
};

// ********************************* My Solution - [Simple Simulation] *********************************
