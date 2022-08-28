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
    TreeNode* correctBinaryTree(TreeNode* root) {
        unordered_map<int, pair<int, TreeNode *> > info;
        queue<TreeNode *> que;
        info[root -> val] = {0, nullptr};
        que.push(root);
        while(!que.empty()) {
            TreeNode *rt = que.front();
            pair<int, TreeNode *> nxt = {info[rt -> val].first + 1, rt};
            que.pop();
            if(rt -> right != nullptr && info.count(rt -> right -> val)) {
                TreeNode *up = info[rt -> val].second;
                if(up -> left == rt) {
                    up -> left = nullptr;
                } else {
                    up -> right = nullptr;
                }
                continue;
            }
            for(TreeNode *tr: {rt -> left, rt -> right}) {
                if(tr == nullptr)
                    continue;
                info[tr -> val] = nxt;
                que.push(tr);
            }
        }
        return root;
    }
};
