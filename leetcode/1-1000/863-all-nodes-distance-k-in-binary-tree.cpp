/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void dfs(TreeNode *rt, unordered_map<int, vector<int> > &e) {
        if(rt == nullptr)
            return;
        if(rt -> left != nullptr) {
            dfs(rt -> left, e);
            e[rt -> val].push_back((rt -> left) -> val);
            e[(rt -> left) -> val].push_back(rt -> val);
        }
        if(rt -> right != nullptr) {
            dfs(rt -> right, e);
            e[rt -> val].push_back((rt -> right) -> val);
            e[(rt -> right) -> val].push_back(rt -> val);
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if(!k)
            return {target -> val};
        unordered_map<int, vector<int> > e;
        dfs(root, e);
        queue<int> que;
        vector<int> ans;
        unordered_map<int, int> dis;
        que.push(target -> val);
        dis[que.front()] = 0;
        while(!que.empty()) {
            int u = que.front(), dist = dis[u] + 1;
            que.pop();
            for(int v: e[u])
                if(!dis.count(v)) {
                    dis[v] = dist;
                    if(dist == k) {
                        ans.push_back(v);
                    } else {
                        que.push(v);
                    }
                }
        }
        return ans;
    }
};
