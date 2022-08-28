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
    void dfs(Node *rt, int dep, vector<vector<int> > &ret) {
        if(rt == nullptr)
            return;
        if(dep == ret.size())
            ret.push_back({});
        ret[dep].push_back(rt -> val);
        for(Node *tr: rt -> children)
            dfs(tr, dep + 1, ret);
    }
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int> > ret;
        dfs(root, 0, ret);
        return ret;
    }
};
