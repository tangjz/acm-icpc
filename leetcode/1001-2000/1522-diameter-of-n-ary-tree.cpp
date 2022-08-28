/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
    int dfs(Node *rt, int &ans) {
        if(rt == nullptr)
            return 0;
        int ret = 0;
        for(Node *tr: rt -> children) {
            if(tr == nullptr)
                continue;
            int tmp = dfs(tr, ans) + 1;
            ans = max(ans, ret + tmp);
            ret = max(ret, tmp);
        }
        return ret;
    }
public:
    int diameter(Node* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
