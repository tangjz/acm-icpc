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
class BSTIterator {
    stack<TreeNode *> stk;

    void extend() {
        TreeNode *cur = stk.top();
        while(cur -> left != nullptr) {
            cur = cur -> left;
            stk.push(cur);
        }
    }
public:
    BSTIterator(TreeNode* root) {
        stk = {};
        if(root != nullptr) {
            stk.push(root);
            extend();
        }
    }

    int next() {
        TreeNode *cur = stk.top();
        stk.pop();
        if(cur -> right != nullptr) {
            stk.push(cur -> right);
            extend();
        }
        return cur -> val;
    }

    bool hasNext() {
        return !stk.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
