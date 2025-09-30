/*
    Use case: Finding pairs with a target sum
    Time: O(n)
*/

// Works only on sorted arrays.
bool hasPairSum(vector<int>& a, int target) {
    int i = 0, j = a.size() - 1;
    while (i < j) {
        int sum = a[i] + a[j];
        if (sum == target) return true;
        else if (sum < target) i++;
        else j--;
    }
    return false;
}


