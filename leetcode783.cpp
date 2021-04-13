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
class Solution {
public:
    int minDiffInBST(TreeNode* root) {
        pre = -0x3f3f3f3f;
        return dfs(root);
    }
private:
    int pre;
    int dfs(TreeNode* now) {
        int res = 0x3f3f3f3f;
        if(now->left != nullptr)    res = dfs(now->left);
        res = min(res, now->val - pre);
        pre = now->val;
        if(now->right != nullptr)   res = min(dfs(now->right), res);
        return res;
    }
};