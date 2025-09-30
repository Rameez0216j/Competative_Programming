/*
    Use case: Removing duplicates from a sorted array in-place
    Time: O(n)
    Space: O(1)
*/
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int j = 1; j < nums.size(); j++) {
        if (nums[j] != nums[i])
            nums[++i] = nums[j];
    }
    return i + 1;
}
