// ****************************************** My Solution ******************************************
class Solution {
    public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n=arr.size();
        int ones=0;
        int zeros=0;

        for(int i=0;i<n;i++) arr[i]==1 ? ones++ : zeros++;

        if(ones%3 != 0 ) return {-1,-1};
        if(ones==0) return {0,n-1};

        int start1=-1;
        int start2=-1;
        int start3=-1;

        int k=ones/3;
        int count=0;
        for(int i=0;i<n;i++){
            if (arr[i]==1){
                count++;
                if(count==1) start1=i;
                if(count==(k+1)) start2=i;
                if(count==(2*k+1)) start3=i;
            }
        }

        
        while(start3 < n){
            if(arr[start1]!=arr[start2] || arr[start2]!=arr[start3]) return {-1,-1};
            start1++,start2++,start3++;
        }

        return {start1-1,start2};
    }
};
// ****************************************** My Solution ******************************************



// ****************************************** My Solution [With Comments] ******************************************
/*
class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int ones = 0;
        int zeros = 0;

        // Count number of 1s and 0s (note: zeros is unused in the logic below)
        for (int i = 0; i < n; i++) arr[i] == 1 ? ones++ : zeros++;

        // If total 1s can't be divided into 3 equal parts, return [-1, -1]
        if (ones % 3 != 0) return {-1, -1};

        // If no 1s, we can split anywhere (e.g., [0, n-1])
        if (ones == 0) return {0, n - 1};

        int start1 = -1, start2 = -1, start3 = -1;

        int k = ones / 3; // Number of 1s in each part
        int count = 0;

        // Find the starting index of the 1st, 2nd, and 3rd part
        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                count++;
                if (count == 1) start1 = i;
                if (count == k + 1) start2 = i;
                if (count == 2 * k + 1) start3 = i;
            }
        }

        // Compare bits from all three parts. They must be equal to be valid.
        while (start3 < n) {
            // If any bit mismatches, return [-1, -1]
            if (arr[start1] != arr[start2] || arr[start2] != arr[start3])
                return {-1, -1};
            // Move all pointers one step forward
            start1++;
            start2++;
            start3++;
        }

        // If valid, return the split indices:
        // [0, start1-1], [start1, start2-1], [start2, n-1]
        return {start1 - 1, start2};
    }
};
*/
// ****************************************** My Solution [With Comments] ******************************************
