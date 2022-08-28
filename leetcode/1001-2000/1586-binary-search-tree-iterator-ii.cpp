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
    int pos;
    vector<TreeNode *> his;
    stack<TreeNode *> stk;
    
    void extend(TreeNode *rt) {
        for( ; rt != nullptr; rt = rt -> left)
            stk.push(rt);
    }
    
    void pick() {
        his.push_back(stk.top());
        stk.pop();
        extend(his.back() -> right);
    }
    
public:
    BSTIterator(TreeNode* root) {
        pos = -1;
        vector<TreeNode *>().swap(his);
        stack<TreeNode *>().swap(stk);
        extend(root);
    }
    
    bool hasNext() {
        return pos + 1 < his.size() || !stk.empty();
    }
    
    int next() {
        if((++pos) == (int)his.size())
            pick();
        return his[pos] -> val;
    }
    
    bool hasPrev() {
        return pos > 0;
    }
    
    int prev() {
        return his[--pos] -> val;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */
