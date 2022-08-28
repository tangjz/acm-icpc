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
    void dfs(TreeNode *rt, string &cur, string &ans) {
        cur.push_back('a' + (rt -> val));
        bool isLeaf = true;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            isLeaf = false;
            dfs(tr, cur, ans);
        }
        if(isLeaf) {
            string tmp = cur;
            reverse(tmp.begin(), tmp.end());
            ans = ans == "" ? tmp : min(ans, tmp);
        }
        cur.pop_back();
    }
public:
    string smallestFromLeaf(TreeNode* root) {
        string ans = "", tmp = "";
        dfs(root, tmp, ans);
        return ans;
    }
};
