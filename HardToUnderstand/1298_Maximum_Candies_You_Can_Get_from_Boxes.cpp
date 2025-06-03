// ************************************************ My Solution ************************************************
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n=status.size();
        vector<bool> visited(n,false);
        vector<bool> boxAvailable(n,false);
        vector<bool> keyAvailable(n,false);
        for(int i=0;i<n;i++) keyAvailable[i]=(status[i]==1); // you missed this line (Be careful)

        queue<int> q;
        for(int box:initialBoxes){
            boxAvailable[box]=true;
            if(status[box]==1){
                visited[box]=true;
                q.push(box);
            }
        }


        int totalCandies=0;
        while(!q.empty()){
            int box=q.front();
            q.pop();

            // Collect the candies
            totalCandies+=candies[box];

            // You have 2 things to do here
            // 1 ==> Picking all the keys and checking if the box for that particular key is available if yes then go check it
            for(int key : keys[box]){
                keyAvailable[key]=true;
                // Checking if box is available and is not into the queue
                if(boxAvailable[key] && !visited[key]){
                    visited[key]=true;
                    q.push(key); // pushed the new openable box
                }
            }

            // 2 ==> Picking all the newBoxes and checking if the key for that particular box is available if yes then go check it
            for(int newBox:containedBoxes[box]){
                boxAvailable[newBox]=true;
                // Checking if box is available and is not into the queue
                if(keyAvailable[newBox] && !visited[newBox]){
                    visited[newBox]=true;
                    q.push(newBox); // pushed the new openable box
                }
            }
        }

        return totalCandies;
    }
};
// ************************************************ My Solution ************************************************
