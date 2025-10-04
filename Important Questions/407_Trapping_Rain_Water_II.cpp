// Solution : https://www.youtube.com/watch?v=TzsbIDtTlsQ
// ********************************** My Solution **********************************
struct CompareFirstElement {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        return a[2] > b[2];
    }
};

class Solution {
    public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n=heightMap.size();
        int m=heightMap[0].size();
        priority_queue<vector<int>, vector<vector<int>>, CompareFirstElement> pq;
        int waterTrapped=0;

        vector<vector<bool>> visited(n,vector<bool>(m,false));
        for(int i=0;i<n;i++){
            pq.push({i,0,heightMap[i][0]}); // first col
            pq.push({i,m-1,heightMap[i][m-1]}); // last col
            visited[i][0]=true;
            visited[i][m-1]=true;
        }

        for(int j=0;j<m;j++){
            pq.push({0,j,heightMap[0][j]}); // first row
            pq.push({n-1,j,heightMap[n-1][j]}); // last row
            visited[0][j]=true;
            visited[n-1][j]=true;
        }

        // Now Supress boundaries inwards
        while(!pq.empty()){
            int currRow=pq.top()[0];
            int currCol=pq.top()[1];
            int currHeight=pq.top()[2];
            pq.pop();


            int r[]={1,-1,0,0};
            int c[]={0,0,1,-1};

            for(int i=0;i<4;i++){
                int newRow=currRow+r[i];
                int newCol=currCol+c[i];

                if(newRow>=0 && newRow<n && newCol>=0 && newCol<m && !visited[newRow][newCol]){
                    int waterOnTop=currHeight-heightMap[newRow][newCol];
                    if(waterOnTop >= 0){
                        waterTrapped+=waterOnTop;
                        visited[newRow][newCol]=true;
                        pq.push({newRow,newCol,currHeight}); // currHeight => as this is the min boundary height seen till now
                    }else{
                        visited[newRow][newCol]=true;
                        pq.push({newRow,newCol,heightMap[newRow][newCol]});// heightMap[newRow][newCol] > currHeight => as this is the min boundary height seen till now
                    }
                }
            }
        }

        return waterTrapped;
    }
};
// ********************************** My Solution **********************************
