/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void dfs(Node *rt, unordered_map<char, int> &ctr, int sgn) {
        if(rt == nullptr)
            return;
        if(rt -> val != '+') {
            ctr[rt -> val] += sgn;
            return;
        }
        dfs(rt -> left, ctr, sgn);
        dfs(rt -> right, ctr, sgn);
    }
public:
    bool checkEquivalence(Node* root1, Node* root2) {
        unordered_map<char, int> ctr;
        dfs(root1, ctr, 1);
        dfs(root2, ctr, -1);
        for(auto &it: ctr)
            if(it.second)
                return 0;
        return 1;
    }
};
