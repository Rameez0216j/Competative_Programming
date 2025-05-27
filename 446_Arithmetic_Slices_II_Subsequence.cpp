// *************************** My Solution [TLE] ==> DP conversion causes MLE ***************************
/*
// Linits ==> LONG_MIN, LONG_MAX, ULLONG_MAX, LLONG_MIN, LLONG_MAX, ULLONG_MAX
class Solution {
    public:
    int solveRec(int ind,int count,long long int prev,long long int diff,vector<int>& nums){
        if(ind>=nums.size()){
            if(count<3) return 0;
            return 1; 
        }

        int case1=0;
        int case2=0;
        if(prev==LONG_MIN){
            case1=solveRec(ind+1,count+1,nums[ind],diff,nums); // select
            case2=solveRec(ind+1,count,prev,diff,nums); // not select
        }else if(diff==LONG_MIN){
            long long int new_diff=nums[ind]-prev;
            case1=solveRec(ind+1,count+1,nums[ind],new_diff,nums); // select
            case2=solveRec(ind+1,count,prev,diff,nums); // not select
        }else{
            long long int new_diff=nums[ind]-prev;
            if(new_diff==diff) case1=solveRec(ind+1,count+1,nums[ind],new_diff,nums); // select
            case2=solveRec(ind+1,count,prev,diff,nums); // not select
        }

        return case1+case2;
    }

    int numberOfArithmeticSlices(vector<int>& nums) {
        // Recursion
        return solveRec(0,0,LONG_MIN,LONG_MIN,nums);
    }
};
*/
// *************************** My Solution [TLE] ==> DP conversion causes MLE ***************************






// Solution : https://www.youtube.com/watch?v=cau0JE1q_ZA&t=844s
// ***************************************** My Solution [Hashmaps] *****************************************
class Solution {
    public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n=nums.size();
        vector<unordered_map<long long int,int>> tracker(n); // vector ==> {common_diff, count}

        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                long long int diff=1LL* nums[i]-nums[j];
                // if(nums[j][diff]!=0) ans+=nums[j][diff];
                ans+=tracker[j][diff];
                // We use tracker[j][diff] instead of tracker[i][diff] because:
                // At index j, we might already have sequences ending with some common difference `diff`.
                // By adding nums[i], we are extending those sequences (making them longer).
                // Only sequences of length ≥ 2 at j can be extended to length ≥ 3 by including nums[i].
                // So, we add tracker[j][diff] to the answer — these are all sequences of length ≥ 2
                // that become valid (length ≥ 3) arithmetic subsequences ending at i.

                tracker[i][diff]+=tracker[j][diff]+1;  // Most important Line (You forgot this logic last time)
            }
        }

        return ans;
    }
};
// ***************************************** My Solution [Hashmaps] *******************************************