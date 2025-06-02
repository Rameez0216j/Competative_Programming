// 1 <= startTime[i] < endTime[i] <= 10^9 ==>Normal Memoizatio ==> TLE || Use Binary search
// ***************************************** My Solution 1 [TLE even with DP] *****************************************
/*
class Solution {
    public:
    int solveRec(int ind,int prev,vector<vector<int>> &jobs){
        if(ind>=jobs.size()) return 0;
        
        int selected=0;
        if(prev==-1 || (jobs[prev][1]<=jobs[ind][0])) selected=jobs[ind][2]+solveRec(ind+1,ind,jobs);
        int notSelected=solveRec(ind+1,prev,jobs);

        return max(selected,notSelected);
    }

    int solveRecMem(int ind,int prev,vector<vector<int>> &jobs,vector<vector<int>> &dp){
        if(ind>=jobs.size()) return 0;

        // NOTE:
        //     We use prev + 1 as an index shift because 'prev' can be -1 (no previous job selected).
        //     To handle negative indices in the DP table, we offset by +1 to map the range [-1, n-1] to [0, n].
        //     If a value can range from -n to n in DP, we apply an offset of +n
        //     to shift the range to [0, 2n] for valid indexing in the DP table.

        if(dp[ind][prev+1]!=-1) return dp[ind][prev+1];

        int selected=0;
        if(prev==-1 || (jobs[prev][1]<=jobs[ind][0])) selected=jobs[ind][2]+solveRecMem(ind+1,ind,jobs,dp);
        int notSelected=solveRecMem(ind+1,prev,jobs,dp);

        return dp[ind][prev+1]=max(selected,notSelected);
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n=profit.size();
        vector<vector<int>> jobs; // ==> {start,end,profit}
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }

        auto comp=[](vector<int> &a,vector<int> &b){
            return a[0]<b[0];
        };
        sort(jobs.begin(),jobs.end(),comp);

        // Recursion
        // return solveRec(0,-1,jobs);

        vector<vector<int>> dp(n,vector<int>(n+1,-1));
        return solveRecMem(0,-1,jobs,dp);
    }
};
*/
// ***************************************** My Solution 1 [TLE even with DP] *****************************************








// 1 <= startTime[i] < endTime[i] <= 10^9 ==>Normal Memoizatio ==> TLE || Use Binary search
// ***************************************** My Solution 2 [TLE even with DP] *****************************************
/*
class Job{
    public:
    int start;
    int end;
    int profit;

    Job(int start,int end,int profit) : start(start), end(end), profit(profit) {};
};

class Solution {
    public:
    int solveRec(int ind,int prev,vector<Job> &jobs){
        if(ind>=jobs.size()) return 0;
        
        int selected=0;
        if(prev==-1 || (jobs[prev].end<=jobs[ind].start)) selected=jobs[ind].profit+solveRec(ind+1,ind,jobs);
        int notSelected=solveRec(ind+1,prev,jobs);

        return max(selected,notSelected);
    }

    int solveRecMem(int ind,int prev,vector<Job> &jobs,vector<vector<int>> &dp){
        if(ind>=jobs.size()) return 0;
        
        // NOTE:
        //    We use prev + 1 as an index shift because 'prev' can be -1 (no previous job selected).
        //    To handle negative indices in the DP table, we offset by +1 to map the range [-1, n-1] to [0, n].
        //    If a value can range from -n to n in DP, we apply an offset of +n
        //    to shift the range to [0, 2n] for valid indexing in the DP table.
        
        if(dp[ind][prev+1]!=-1) return dp[ind][prev+1];

        int selected=0;
        if(prev==-1 || (jobs[prev].end<=jobs[ind].start)) selected=jobs[ind].profit+solveRecMem(ind+1,ind,jobs,dp);
        int notSelected=solveRecMem(ind+1,prev,jobs,dp);

        return dp[ind][prev+1]=max(selected,notSelected);
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n=profit.size();
        vector<Job> jobs; // ==> {start,end,profit}
        for(int i=0;i<n;i++){
            
            // ❌ Why it's wrong:
            // new Job(...) returns a pointer to a dynamically allocated Job.
            // But jobs is a vector of objects (vector<Job>), not pointers (vector<Job*>).
            // So you're trying to push a Job* into a vector<Job>, which is a type mismatch and leads to a compile-time error.
            
            // jobs.push_back(new Job(startTime[i],endTime[i],profit[i]));
            jobs.push_back(Job(startTime[i],endTime[i],profit[i]));
        }

        auto comp=[](Job &a,Job &b){
            return a.start<b.start;
        };
        sort(jobs.begin(),jobs.end(),comp);

        // Recursion
        // return solveRec(0,-1,jobs);

        vector<vector<int>> dp(n,vector<int>(n+1,-1));
        return solveRecMem(0,-1,jobs,dp);
    }
};
*/
// ***************************************** My Solution 2 [TLE even with DP] *****************************************







// Solution : https://www.youtube.com/watch?v=LL0tVxlAeV4&t=1184s
// 1 <= startTime[i] < endTime[i] <= 10^9 ==>Normal Memoizatio ==> TLE || Use Binary search
// ***************************************** My Solution 3 [Binary search with DP] *****************************************
class Job{
    public:
    int start;
    int end;
    int profit;

    Job(int start,int end,int profit) : start(start), end(end), profit(profit) {};
};

class Solution {
    public:
    int getNext(int ind,vector<Job> &jobs){
        int ans=jobs.size();
        int currEnd=jobs[ind].end;

        int start=ind+1;
        int end=jobs.size()-1;
        while(start<=end){
            int mid=start+(end-start)/2;
            if(jobs[mid].start>=currEnd){
                ans=mid;
                end=mid-1;
            }else start=mid+1;
        }
        return ans;
    }

    int solveRec(int ind,vector<Job> &jobs){
        if(ind>=jobs.size()) return 0;

        int nextInd=getNext(ind,jobs); // select current and search next from ind+1 till last
        int selected=jobs[ind].profit+solveRec(nextInd,jobs);
        int notSelected=solveRec(ind+1,jobs);

        return max(selected,notSelected);
    }

    int solveRecMem(int ind,vector<Job> &jobs,vector<int> &dp){
        if(ind>=jobs.size()) return 0;

        if(dp[ind]!=-1) return dp[ind];

        int nextInd=getNext(ind,jobs); // select current and search next from ind+1 till last
        int selected=jobs[ind].profit+solveRecMem(nextInd,jobs,dp);
        int notSelected=solveRecMem(ind+1,jobs,dp);

        return dp[ind]=max(selected,notSelected);
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n=profit.size();
        vector<Job> jobs; // ==> {start,end,profit}
        for(int i=0;i<n;i++){
            /*
                ❌ Why it's wrong:
                new Job(...) returns a pointer to a dynamically allocated Job.
                But jobs is a vector of objects (vector<Job>), not pointers (vector<Job*>).
                So you're trying to push a Job* into a vector<Job>, which is a type mismatch and leads to a compile-time error.
            */
            // jobs.push_back(new Job(startTime[i],endTime[i],profit[i]));
            jobs.push_back(Job(startTime[i],endTime[i],profit[i]));
        }

        auto comp=[](Job &a,Job &b){
            return a.start<b.start;
        };
        sort(jobs.begin(),jobs.end(),comp);

        // Recursion
        // return solveRec(0,jobs);

        // Recursion + Memoization
        vector<int> dp(n,-1);
        return solveRecMem(0,jobs,dp);
    }
};
// ***************************************** My Solution 3 [Binary search with DP] *****************************************