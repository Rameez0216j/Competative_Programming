// Minimujm swaps to sort an array ( you can choose any 2 indiceds and swap them at a time)
int findOps(vector<int> &level){
    int n=level.size();
    vector<pair<int,int>> arr;
    for(int i=0;i<n;i++) arr.push_back({level[i],i});
    sort(arr.begin(),arr.end());
    int ops=0;
    
    vector<int> visited(n,false);
    for(int i=0;i<n;i++){
        if(visited[i] || arr[i].second==i) continue;
        int currInd=arr[i].second;
        int cycleSize=0;
        while(!visited[currInd]){
            visited[currInd]=true;
            currInd=arr[currInd].second;
            cycleSize++;
        }
        
        if(cycleSize>0) ops+=(cycleSize-1);
    }
    return ops;
}
