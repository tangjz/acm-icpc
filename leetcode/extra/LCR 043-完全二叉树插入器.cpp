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
class CBTInserter {
    vector<TreeNode *> seq;
public:
    CBTInserter(TreeNode* root) {
        seq = {nullptr, root};
        for(int i = 1; i < (int)seq.size(); ++i) {
            TreeNode *rt = seq[i];
            if(rt -> left == nullptr)
                break;
            seq.push_back(rt -> left);
            if(rt -> right == nullptr)
                break;
            seq.push_back(rt -> right);
        }
    }

    int insert(int val) {
        int x = seq.size();
        seq.push_back(new TreeNode(val));
        (x & 1 ? seq[x >> 1] -> right : seq[x >> 1] -> left) = seq[x];
        return seq[x >> 1] -> val;
    }

    TreeNode* get_root() {
        return seq[1];
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
