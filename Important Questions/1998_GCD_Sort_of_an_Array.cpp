// Solution : https://www.youtube.com/watch?v=RASAjylxIPo
// ********************************************** My Solution [DSU] **********************************************
/*
    ##################################  WRONG SNIPPETS TO AVOID  ##################################
    auto comp = [&](int &a, int &b) {
        int p1 = findParent(a, parent);
        int p2 = findParent(b, parent);

        ❌ WRONG:
        This comparator attempts to sort elements based on their DSU (disjoint set) parent.

        🧨 WHY WRONG:
        - The purpose of `gcdSort` is not to sort based on DSU parents.
        - Sorting by parent ID doesn't ensure a valid sequence of swaps using common GCD factors.
        - Even if two numbers are in the same component, using `a > b` arbitrarily may break the sort.

        ✅ CORRECT APPROACH:
        - Sort a copy of the original array normally.
        - Check for each index if the original and sorted elements belong to the same DSU component.
        - If not, return false.
        
        if (p1 == p2) return a > b;
        return a <= b;
    };
    */

    /*
    int findParent(int a, vector<int> &parent) {
        int num = a;

        ❌ SYNTAX ERROR:
        while (parent[num] != num])  ← extra closing bracket ']' causes compilation failure

        ✅ FIX:
        while (parent[num] != num)

        ❌ LOGICAL ERROR:
        Only compresses the path for `a`, not for other nodes in the path.

        🧨 WHY WRONG:
        - This weak compression leads to inefficient DSU behavior in repeated queries.
        - DSU path compression should update all nodes in the path from `a` to root.

        ✅ CORRECT VERSION:
        int findParent(int a, vector<int>& parent) {
            if (parent[a] != a)
                parent[a] = findParent(parent[a], parent); // Recursively compress the path
            return parent[a];
        }

        while (parent[num] != num) num = parent[num];
        parent[a] = num;
        return parent[a];
    }
*/



class Solution {
    public:
    // Most Important
    int findParent(int a, vector<int>& parent) {
        if (parent[a] != a) parent[a] = findParent(parent[a], parent);  // Recursively compress the path
        return parent[a];
    }

    void unite(int a, int b, vector<int>& parent) {
        int p1 = findParent(a, parent);
        int p2 = findParent(b, parent);
        if (p1 != p2)
            parent[p1] = p2;  // Union operation
    }

    vector<int> findFactors(int num){
        vector<int> factors;
        if(num<1) return {};
        if(num%2==0){
            factors.push_back(2);
            while(num%2==0) num=num/2;
        }

        for(int i=3;i*i<=num;i+=2){
            if(num%i==0) factors.push_back(i);
            while(num%i==0) num=num/i;
        }

        if (num > 1) factors.push_back(num);
        return factors;
    }

    bool gcdSort(vector<int>& nums) {
        int maxi=*max_element(nums.begin(),nums.end());
        vector<int> parent(maxi+1,0);
        iota(parent.begin(), parent.end(), 0);

        for(int num:nums){
            vector<int> primeFactors=findFactors(num);
            for(int primeFactor:primeFactors){
                unite(primeFactor,num,parent);
            }
        }

        
        vector<int> sorted=nums;
        sort(sorted.begin(),sorted.end());

        for(int i=0;i<nums.size();i++){
            // Always use findParent function for finding parent never use direct accessing via array
            int p1=findParent(nums[i],parent);
            int p2=findParent(sorted[i],parent);
            if(p1!=p2) return false;
        }
        return true;
    }
};
// ********************************************** My Solution [DSU] **********************************************