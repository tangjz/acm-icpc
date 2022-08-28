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
    bool isCousins(TreeNode* root, int x, int y) {
        unordered_map<int, pair<int, int> > info;
        queue<TreeNode *> que;
        auto extend = [&](TreeNode *rt) {
            // if(rt == nullptr)
            //     return;
            pair<int, int> tmp = info[rt -> val];
            tmp = {tmp.first + 1, rt -> val};
            for(TreeNode *ch: {rt -> left, rt -> right}) {
                if(ch == nullptr)
                    continue;
                // printf("%d: %d %d\n", ch -> val, tmp.first, tmp.second);
                info[ch -> val] = tmp;
                que.push(ch);
            }
        };
        info[root -> val] = {0, 0};
        que.push(root);
        while(!que.empty()) {
            extend(que.front());
            que.pop();
        }
        pair<int, int> u = info[x], v = info[y];
        return u.first == v.first && u.second != v.second;
    }
};
