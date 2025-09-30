// ************************************** My Solution  **************************************
class Solution {
    public:
    int KadaneRange(vector<int>& diff) {
        int res = diff[0];           
        int maxEnding = diff[0];     

        for (int i = 1; i < diff.size(); i++) {
            maxEnding = max(diff[i], maxEnding + diff[i]);
            res = max(res, maxEnding);
        }
        return res;
    }

    
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        vector<int> diff1(n),diff2(n);
        int sum1=0;
        int sum2=0;

        for(int i=0;i<n;i++){
            diff1[i]=nums1[i]-nums2[i];
            diff2[i]=nums2[i]-nums1[i];
            sum1+=nums1[i];
            sum2+=nums2[i];
        }

        int val1=KadaneRange(diff1);
        int val2=KadaneRange(diff2);

        // Method1
        // int ans=max(sum1,sum2);
        // ans=max(ans,max(sum1-val1,sum2+val1));
        // ans=max(ans,max(sum2-val2,sum1+val2));
        // return ans;

        // Method2
        return max(sum1+val2,sum2+val1);
    }
};
// ************************************** My Solution  **************************************