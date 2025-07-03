/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// ******************************************* My Solution [Normal] *******************************************
/*
class Solution {
    int cameras=0;

    public:
    int solveRec(TreeNode* root){
        if(root==NULL) return 1; 

        int left=1; // consder as monitored as they may be null
        int right=1;
        if(root->left) left=solveRec(root->left);
        if(root->right) right=solveRec(root->right);

        if(left==-1 || right==-1){
            cameras++;
            return 0;
        }

        if(left==0 || right==0) return 1;

        return -1;
    }

    int minCameraCover(TreeNode* root) {
        if(solveRec(root)==-1) cameras++;
        return cameras;
    }
};
*/
// ******************************************* My Solution [Normal] *******************************************





// ******************************************* My Solution [With Enum] *******************************************
class Solution {
    int cameras = 0;

    enum State {
        NEEDS_CAMERA,   // Node is not monitored by any camera
        HAS_CAMERA,     // Node has a camera
        MONITORED       // Node is monitored (child has a camera)
    };

    State solveRec(TreeNode* root) {
        if (root == nullptr)
            return MONITORED; // Null nodes are considered monitored

        State left = solveRec(root->left);
        State right = solveRec(root->right);

        // If either child needs a camera, place camera at current node
        if (left == NEEDS_CAMERA || right == NEEDS_CAMERA) {
            cameras++;
            return HAS_CAMERA;
        }

        // If either child has a camera, this node is monitored
        if (left == HAS_CAMERA || right == HAS_CAMERA)
            return MONITORED;

        // Otherwise, this node needs a camera
        return NEEDS_CAMERA;
    }

    public:
    int minCameraCover(TreeNode* root) {
        if (solveRec(root) == NEEDS_CAMERA)
            cameras++; // Final camera at root if needed
        return cameras;
    }
};
// ******************************************* My Solution [With Enum] *******************************************