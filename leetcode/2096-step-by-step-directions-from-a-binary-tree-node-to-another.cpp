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
    string getDirections(TreeNode* root, int u, int v) {
        int n = 0;
        vector<int> dep, rnk;
        vector<pair<TreeNode *, TreeNode *> > que;
        que.push_back({root, nullptr});
        for(int i = 0; i < (int)que.size(); ++i) {
            TreeNode *cur = que[i].first, *pre = que[i].second;
            int id = cur -> val;
            if(n <= id) {
                n = id + 1;
                dep.resize(n);
                rnk.resize(n);
            }
            if(i == 0) {
                dep[id] = 0;
            } else {
                dep[id] = dep[pre -> val] + 1;
            }
            for(TreeNode *nxt : {cur -> left, cur -> right})
                if(nxt != nullptr)
                    que.push_back({nxt, cur});
            rnk[id] = i;
        }
        string ret = "";
        int x = u, y = v, z;
        while(x != y) {
            if(dep[x] < dep[y]) {
                int i = rnk[y];
                TreeNode *cur = que[i].first, *pre = que[i].second;
                ret.push_back(pre -> left == cur ? 'L' : 'R');
                y = pre -> val;
            } else {
                int i = rnk[x];
                TreeNode *cur = que[i].first, *pre = que[i].second;
                x = pre -> val;
            }
        }
        for(int i = dep[u] - dep[x]; i > 0; --i, ret.push_back('U'));
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
