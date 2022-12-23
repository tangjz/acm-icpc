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
    static const int INF = 0x3f3f3f3f;
    struct Info {
        int f[2][2];
    };
    Info dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {};
        Info lft = dfs(rt -> left), rht = dfs(rt -> right), ret;
        for(int u = 0; u < 2; ++u)
            for(int v = 0; v < 2; ++v)
                ret.f[u][v] = INF;
        int u = rt -> val;
        for(int v = 0; v < 2; ++v)
            for(int w = 0; w < 2; ++w) {
                if(lft.f[v][w] == INF || rht.f[v][w] == INF)
                    continue;
                for(int msk = 0; msk < 8; ++msk) {
                    int uu = u, vv = v, ww = w, cc = 0;
                    if(msk & 1) {
                        uu = !uu;
                        ++cc;
                    }
                    if(msk & 2) {
                        uu = !uu;
                        vv = !vv;
                        ww = !ww;
                        ++cc;
                    }
                    if(msk & 4) {
                        uu = !uu;
                        vv = !vv;
                        ++cc;
                    }
                    if(vv == ww) {
                        ret.f[uu][vv] = min(ret.f[uu][vv], lft.f[v][w] + rht.f[v][w] + cc);
                    }
                }
            }
        return ret;
    }
public:
    int closeLampInTree(TreeNode* root) {
        return dfs(root).f[0][0];
    }
};
