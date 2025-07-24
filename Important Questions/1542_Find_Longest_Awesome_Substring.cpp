// Solution : https://www.youtube.com/watch?v=rZPCi5JySY4
// ********************************************* My Solution *********************************************
class Solution {
    public:
    int longestAwesome(string s) {
        int n=s.size();
        int mask=0b0000000000;  // 10 zeroes ==> 0 -> even Count, 1 -> odd Count

        int ans=0;
        unordered_map<int,int> indicesTracker;
        indicesTracker[0]=-1;
        for(int i=0;i<n;i++){
            mask=(mask ^ (1<<(s[i]-'0'))); // flip the bit
            if(indicesTracker.count(mask)){
                ans=max(ans,(i-indicesTracker[mask]));
            }

            for(int j=0;j<=9;j++){
                int finder=1<<j;
                int new_mask=mask^finder;
                if(indicesTracker.count(new_mask)){
                    ans=max(ans,i-indicesTracker[new_mask]);
                }
            }

            if(indicesTracker.count(mask)) continue;
            indicesTracker[mask]=i;
        }

        return ans;
    }
};
// ********************************************* My Solution *********************************************