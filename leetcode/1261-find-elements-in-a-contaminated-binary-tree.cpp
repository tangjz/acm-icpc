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
class FindElements {
    TreeNode *root;
public:
    FindElements(TreeNode* root) {
        this -> root = root;
    }
    
    bool find(int target) {
        ++target;
        int mx = 0;
        for( ; (1 << mx) <= target; ++mx);
        TreeNode *cur = root;
        for(int i = mx - 2; i >= 0; --i) {
            if((target >> i) & 1) {
                cur = cur -> right;
            } else {
                cur = cur -> left;
            }
            if(cur == nullptr)
                return 0;
        }
        return 1;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
