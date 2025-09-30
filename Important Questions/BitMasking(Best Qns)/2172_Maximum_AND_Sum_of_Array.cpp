// Solution : https://www.youtube.com/watch?v=0X0Vss4HTxg
// *********************************************** My Solution ***********************************************
class Solution {
    public:
    /*
    int solveRec(int curr, string availability, int numSlots, vector<int>& nums){
        if(curr>=nums.size()) return 0;

        int res=0;
        for(int slot=1; slot <= numSlots; slot++){
            int status=availability[slot]-'0';
            
            if(status>0){
                string newAvailability = availability;
                newAvailability[slot]--; // newAvailability[slot] = (char)((availability[slot] - '0' - 1) + '0');  // decrement char safely[Preferred]
                res=max(res, (nums[curr]&slot) + solveRec(curr+1,newAvailability,numSlots,nums));

                // res=max(res, nums[curr]&slot + solveRec(curr+1,newAvailability,numSlots,nums)); ==> Wrong 
            }
        }

        return res;
    }
    */


    // Clean code
    int solveRec(int curr, string availability, int numSlots, vector<int>& nums){
        if(curr>=nums.size()) return 0;

        int res=0;
        for(int slot=1; slot <= numSlots; slot++){
            int status=availability[slot]-'0';
            
            if(status>0){
                string newAvailability = availability;
                newAvailability[slot]--;
                res=max(res, (nums[curr]&slot) + solveRec(curr+1,newAvailability,numSlots,nums));
            }
        }
        return res;
    }



    int solveRec_Mem(int curr, string availability, int numSlots, vector<int>& nums, vector<unordered_map<string,int>> &dp){
        if(curr>=nums.size()) return 0;

        if(dp[curr].count(availability)) return dp[curr][availability];

        int res=0;
        for(int slot=1; slot <= numSlots; slot++){
            int status=availability[slot]-'0';
            
            if(status>0){
                string newAvailability = availability;
                newAvailability[slot]--;
                res=max(res, (nums[curr]&slot) + solveRec_Mem(curr+1,newAvailability,numSlots,nums,dp));
            }
        }
        return dp[curr][availability]=res;
    }


    int maximumANDSum(vector<int>& nums, int numSlots) {
        string availability(numSlots+1,'2'); // 0th place is redundant and is left unused 

        // Recursion
        // return solveRec(0,availability,numSlots,nums);

        // Recursion + Memoization
        vector<unordered_map<string,int>> dp(nums.size()+1);
        return solveRec_Mem(0,availability,numSlots,nums,dp);
    }
};
// *********************************************** My Solution ***********************************************