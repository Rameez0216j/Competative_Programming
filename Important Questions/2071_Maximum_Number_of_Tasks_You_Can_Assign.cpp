// Solution : https://www.youtube.com/watch?v=7tGM7XA06MI&t=1255s
// *********************************************** My Solution ***********************************************
class Solution {
    public:
    // Time Complexity ==> O(n) + O(n*log(m)) 
    bool isPossible(int taskCount,vector<int>& tasks, vector<int>& workers,int pills, int strength){
        int count=0;
        if(taskCount>workers.size()) return false;

        multiset<int> availableWorkers;
        for(int i=0;i<taskCount;i++) availableWorkers.insert(workers[i]);

        for(int i=taskCount-1;i>=0;i--){
            auto it=availableWorkers.lower_bound(tasks[i]);
            if(it!=availableWorkers.end()) availableWorkers.erase(it);
            else{
                auto it_improved=availableWorkers.lower_bound(tasks[i]-strength);
                if(it_improved==availableWorkers.end() || pills==0) return false;
                availableWorkers.erase(it_improved);
                pills--;
            }
        }

        return true;
    }

    // Time Complexity = O(log(n) * n * log(m))
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(),tasks.end());
        sort(workers.begin(),workers.end(),greater<int>());

        int high=tasks.size();
        int low=0;
        
        int ans=0;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(isPossible(mid,tasks,workers,pills,strength)){
                ans=mid;
                low=mid+1;
            }else high=mid-1;
        }

        return ans;
    }
};
// *********************************************** My Solution ***********************************************