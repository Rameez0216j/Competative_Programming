// Solution : https://www.youtube.com/watch?v=KVU4JNNJkVg
// **************************** My Solution [2 pointers] ****************************
class Solution {
    public:
    int maxArea(vector<int>& height) {
        int ans=0;
        int n=height.size();
        int i=0;
        int j=n-1;

        while(i<j){
            int height1=height[i];
            int height2=height[j];
            int height=min(height1,height2);

            int width=j-i;
            int currArea=height*width;
            ans=max(currArea,ans);

            if(height1<height2) i++;
            else j--;
        }

        return ans;
    }
};
// **************************** My Solution [2 pointers] ****************************