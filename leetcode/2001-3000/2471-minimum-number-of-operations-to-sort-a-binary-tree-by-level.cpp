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
    void dfs(TreeNode *rt, int dep, vector<vector<int> > &seq) {
        if(rt == nullptr)
            return;
        if(dep == seq.size())
            seq.push_back({});
        seq[dep].push_back(rt -> val);
        dfs(rt -> left, dep + 1, seq);
        dfs(rt -> right, dep + 1, seq);
    }
public:
    int minimumOperations(TreeNode* root) {
        vector<vector<int> > seq;
        dfs(root, 0, seq);
        int ans = 0;
        for(auto &vec: seq) {
            int n = vec.size();
            vector<int> que(vec.begin(), vec.end());
            sort(que.begin(), que.end());
            for(int i = 0; i < n; ++i) {
                // printf("%d%c", vec[i], " \n"[i == n - 1]);
                vec[i] = lower_bound(que.begin(), que.end(), vec[i]) - que.begin();
            }
            ans += n;
            for(int i = 0; i < n; ++i) {
                if(vec[i] == -1)
                    continue;
                --ans;
                for(int j = i, k; vec[j] != -1; k = j, j = vec[j], vec[k] = -1);
            }
        }
        return ans;
    }
};
