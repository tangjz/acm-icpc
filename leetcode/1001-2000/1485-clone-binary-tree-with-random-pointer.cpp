/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     Node *left;
 *     Node *right;
 *     Node *random;
 *     Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
 * };
 */

class Solution {
    NodeCopy *dfs(Node *rt, unordered_map<Node *, NodeCopy *> &Hash) {
        if(rt == nullptr)
            return nullptr;
        NodeCopy *ret = new NodeCopy(rt -> val, dfs(rt -> left, Hash), dfs(rt -> right, Hash), nullptr);
        Hash.insert({rt, ret});
        return ret;
    }
public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        unordered_map<Node *, NodeCopy *> Hash;
        NodeCopy *rt = dfs(root, Hash);
        for(auto &it: Hash)
            if(it.first -> random != nullptr)
                it.second -> random = Hash[it.first -> random];
        return rt;
    }
};
