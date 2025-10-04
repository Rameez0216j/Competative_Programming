// ************************************ My Solution [Union Find] ************************************
class Solution {
    unordered_map<string, string> parent;   // parent of each string
    unordered_map<string, int> rank;        // rank (size/depth) of each set

    public:
    // Find the representative (root) of the set with path compression
    string findRoot(const string& s) {
        if (parent[s] != s) {
            parent[s] = findRoot(parent[s]); // path compression
        }
        return parent[s];
    }

    // Check if two strings are similar (0 or 2 differences)
    bool isSimilar(const string& s1, const string& s2) {
        int diffCount = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) diffCount++;
        }
        return diffCount == 0 || diffCount == 2;
    }

    int numSimilarGroups(vector<string>& strs) {
        // Initialize each string as its own parent with rank 0
        for (const string& s : strs) {
            parent[s] = s;
            rank[s] = 0;
        }

        int n = strs.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isSimilar(strs[i], strs[j])) {
                    string root1 = findRoot(strs[i]);
                    string root2 = findRoot(strs[j]);

                    if (root1 != root2) {
                        // Union by rank
                        if (rank[root1] < rank[root2]) {
                            parent[root1] = root2;
                        } else if (rank[root1] > rank[root2]) {
                            parent[root2] = root1;
                        } else {
                            parent[root2] = root1;
                            rank[root1]++;
                        }
                    }
                }
            }
        }

        // Count unique roots
        set<string> uniqueRoots;
        for (auto& [str, _] : parent) {
            uniqueRoots.insert(findRoot(str));
        }

        return uniqueRoots.size();
    }
};
// ************************************ My Solution [Union Find] ************************************
