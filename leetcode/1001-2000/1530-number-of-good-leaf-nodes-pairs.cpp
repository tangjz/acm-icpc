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
    vector<int> dfs(TreeNode *rt, int dist, int &ans) {
        vector<int> ret(dist);
        bool hasChild = 0;
        for(TreeNode *ch : {rt -> left, rt -> right}) {
            if(ch == NULL)
                continue;
            hasChild = 1;
            vector<int> tmp = dfs(ch, dist, ans);
            for(int i = dist - 1, j = 0, sum = 0; i >= 0; --i, ++j) {
                sum += ret[j];
                ans += tmp[i] * sum;
            }
            for(int i = 1; i < dist; ++i)
                ret[i] += tmp[i - 1];
        }
        if(!hasChild)
            ++ret[0];
        return ret;
    }
public:
    int countPairs(TreeNode* root, int distance) {
        int ans = 0;
        if(root != NULL)
            dfs(root, distance, ans);
        return ans;
    }
};
