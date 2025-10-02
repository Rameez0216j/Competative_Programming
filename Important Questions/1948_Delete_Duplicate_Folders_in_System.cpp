// Solution : https://www.youtube.com/watch?v=QyrmIu4Vo8A
// *********************************** My Solution ***********************************
struct trieNode
{
    string subPathString;
    unordered_map<string, trieNode *> children;
};

class Trie
{
private:
    trieNode *root;

public:
    Trie()
    {
        root = new trieNode();
    }

    void insert(vector<string> &path)
    {
        trieNode *currPtr = root;
        for (string currFolder : path)
        {
            if (currPtr->children[currFolder] == NULL)
                currPtr->children[currFolder] = new trieNode();
            currPtr = currPtr->children[currFolder];
        }
    }

    string traversePostOrder(trieNode *root, unordered_map<string, int> &freq)
    {
        vector<string> subPaths;

        // Traverse children
        for (auto &[name, node] : root->children)
        {
            string subPath = traversePostOrder(node, freq); // recursive
            subPaths.push_back(name + subPath);             // include child's name
        }

        // Sort children to ensure unique serialization
        sort(subPaths.begin(), subPaths.end());

        // Serialize current node's subtree
        string currSubtree = "";
        for (auto &sp : subPaths)
        {
            currSubtree += "(" + sp + ")";
        }

        root->subPathString = currSubtree;
        if (currSubtree != "")
            freq[currSubtree]++; // store frequency
        return currSubtree;
    }

    unordered_map<string, int> getDuplicates()
    {
        unordered_map<string, int> freq;
        traversePostOrder(this->root, freq);
        // traversePostOrder(root,freq); // This will also work
        return freq;
    }

    /*
        void removeDuplicates(trieNode* root,unordered_map<string,int> &freq){
            for (auto &[name, node] : root->children) {
                string subPath = node->subPathString;
                if(freq[subPath]>1) root->children.erase(name);
                else removeDuplicates(node,freq);
            }
        }
        above code is wrong as we are modifiying iterator while iterating over it (causes abnormal behaviour)
    */

    // Correct code
    void removeDuplicates(trieNode *root, unordered_map<string, int> &freq)
    {
        vector<string> toErase;
        for (auto &[name, node] : root->children)
        {
            string subPath = node->subPathString;
            if (freq[subPath] > 1)
                toErase.push_back(name);
            else
                removeDuplicates(node, freq);
        }
        for (auto &name : toErase)
            root->children.erase(name);
    }

    void deleteDuplicates(unordered_map<string, int> &freq)
    {
        removeDuplicates(this->root, freq);
    }

    bool isValidPath(vector<string> &path)
    {
        trieNode *currPtr = root;
        for (string currFolder : path)
        {
            if (currPtr->children[currFolder] == NULL)
                return false;
            else
                currPtr = currPtr->children[currFolder];
        }
        return true;
    }
};

class Solution
{
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &paths)
    {
        Trie trie;

        for (vector<string> &path : paths)
        {
            trie.insert(path);
        }

        unordered_map<string, int> freq = trie.getDuplicates();
        trie.deleteDuplicates(freq);

        vector<vector<string>> ans;
        for (vector<string> &path : paths)
        {
            if (trie.isValidPath(path))
                ans.push_back(path);
        }

        return ans;
    }
};
// *********************************** My Solution ***********************************

// *********************************** My Solution [Optimized] ***********************************
/*
struct trieNode {
    string subPathString;
    map<string, trieNode*> children; // ✅ Changed from unordered_map to map for automatic sorting
};

class Trie {
private:
    trieNode* root;

public:
    Trie() {
        root = new trieNode(); // ✅ root is a pointer
    }

    void insert(vector<string> &path) {
        trieNode* curr = root;
        for (string &folder : path) {
            // ✅ Fixed access: curr->children[folder], not curr[folder]
            if (curr->children[folder] == nullptr)
                curr->children[folder] = new trieNode(); // ✅ Allocate new node if not exists
            curr = curr->children[folder]; // ✅ Move to child node
        }
    }

    string traversePostOrder(trieNode* root, unordered_map<string,int> &freq) {
        string currSubtree;

        // ✅ Changed: No vector + sort needed because children is a map (sorted automatically)
        for (auto &[name, node] : root->children) {
            string subPath = traversePostOrder(node, freq); // recursive traversal
            currSubtree += "(" + name + subPath + ")"; // ✅ Efficient concatenation
        }

        root->subPathString = currSubtree;
        if (!currSubtree.empty()) freq[currSubtree]++; // ✅ Count frequency only if not empty
        return currSubtree;
    }

    unordered_map<string,int> getDuplicates() {
        unordered_map<string,int> freq;
        traversePostOrder(root, freq); // ✅ Call on root pointer
        return freq;
    }

    void removeDuplicates(trieNode* root, unordered_map<string,int> &freq) {
        // ✅ Changed to iterator-based erase to safely remove while iterating
        for (auto it = root->children.begin(); it != root->children.end(); ) {
            if (freq[it->second->subPathString] > 1)
                it = root->children.erase(it); // ✅ erase returns next iterator
            else {
                removeDuplicates(it->second, freq);
                ++it; // ✅ Increment only when not erased
            }
        }
    }

    void deleteDuplicates(unordered_map<string,int> &freq) {
        removeDuplicates(root, freq); // ✅ Call on root pointer
    }

    bool isValidPath(vector<string> &path) {
        trieNode* curr = root;
        for (string &folder : path) {
            if (curr->children[folder] == nullptr) return false; // ✅ Pointer check
            curr = curr->children[folder];
        }
        return true;
    }
};

class Solution {
    public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Trie trie;

        for (vector<string> &path : paths) {
            trie.insert(path); // ✅ Insert all paths
        }

        unordered_map<string,int> freq = trie.getDuplicates(); // ✅ Get subtree frequencies
        trie.deleteDuplicates(freq); // ✅ Remove duplicate subtrees

        vector<vector<string>> ans;
        for (vector<string> &path : paths) {
            if (trie.isValidPath(path)) // ✅ Only include valid paths after deletion
                ans.push_back(path);
        }

        return ans;
    }
};
*/
// *********************************** My Solution [Optimized] ***********************************