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
    vector<int> dfs(TreeNode *rt, int k, int &ans) {
        if(rt == nullptr)
            return {};
        vector<int> ret, pre;
        for(auto ch: {rt -> left, rt -> right}) {
            vector<int> adt = dfs(ch, k, ans);
            ret.swap(pre);
            ret.clear();
            auto it = pre.begin(), jt = adt.begin();
            for(int i = 0; i < k && (it != pre.end() || jt != adt.end()); ++i)
                if(jt == adt.end() || (it != pre.end() && *it < *jt)) {
                    ret.push_back(*(it++));
                } else {
                    ret.push_back(*(jt++));
                }
        }
        if(ret.size() == k && rt -> val > ret.back()) {
            ++ans;
        } else {
            auto it = lower_bound(ret.begin(), ret.end(), rt -> val);
            ret.insert(it, rt -> val);
            if(ret.size() > k)
                ret.pop_back();
        }
        return ret;
    }
public:
    int countGreatEnoughNodes(TreeNode* root, int k) {
        int ans = 0;
        dfs(root, k, ans);
        return ans;
    }
};
