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
    typedef unsigned long long ULL;
    ULL compat(int rt, int lft, int rht) {
        // printf("compat %d %d %d: %lld\n", rt, lft, rht, lft == -1 || rht == -1 ? -1 : ((LL)rt << 10 | lft) << 10 | rht);
        if(lft == -1 || rht == -1)
            return -1;
        return ((ULL)rt << 10 | lft) << 10 | rht;
    }
    int dfs1(TreeNode *rt, unordered_map<ULL, int> &Hash) {
        if(rt == nullptr)
            return 0;
        ULL msk = compat(rt -> val, dfs1(rt -> left, Hash), dfs1(rt -> right, Hash));
        auto it = Hash.find(msk);
        if(it == Hash.end()) {
            int id = Hash.size() + 1;
            Hash.insert({msk, id});
            // printf("hash %lld: %d\n", msk, id);
            return id;
        }
        // printf("found %lld: %d\n", msk, it -> second);
        return it -> second;
    }
    int dfs2(TreeNode *rt, unordered_map<ULL, int> &Hash, int sp, bool &found) {
        if(rt == nullptr)
            return 0;
        ULL msk = compat(rt -> val, dfs2(rt -> left, Hash, sp, found), dfs2(rt -> right, Hash, sp, found));
        if(msk == -1)
            return -1;
        auto it = Hash.find(msk);
        if(it == Hash.end())
            return -1;
        // printf("found %lld: %d\n", msk, it -> second);
        found |= it -> second == sp;
        return it -> second;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        unordered_map<ULL, int> Hash;
        int id = dfs1(subRoot, Hash);
        // printf("id %d\n", id);
        bool found = false;
        dfs2(root, Hash, id, found);
        // puts("");
        return found;
    }
};
