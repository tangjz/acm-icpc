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
    struct Info {
        int sum, low, upp;
        bool good;
        Info(int val) {
            sum = low = upp = val;
            good = 1;
        }
        void mergeLeft(Info const &lft) {
            if(good && lft.good && lft.upp < low) {
                sum += lft.sum;
                low = lft.low;
            } else {
                good = 0;
            }
        }
        void mergeRight(Info const &rht) {
            if(good && rht.good && upp < rht.low) {
                sum += rht.sum;
                upp = rht.upp;
            } else {
                good = 0;
            }
        }
    };
    Info dfs(TreeNode *rt, int &ans) {
        Info cur(rt -> val);
        if(rt -> left != NULL)
            cur.mergeLeft(dfs(rt -> left, ans));
        if(rt -> right != NULL)
            cur.mergeRight(dfs(rt -> right, ans));
        if(cur.good)
            ans = max(ans, cur.sum);
        return cur;
    }
public:
    int maxSumBST(TreeNode* root) {
        int ans = 0;
        if(root != NULL)
            dfs(root, ans);
        return ans;
    }
};
