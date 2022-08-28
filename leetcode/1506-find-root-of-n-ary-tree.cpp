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
public:
    Node* findRoot(vector<Node*> tree) {
        unordered_set<int> nonRoot;
        for(auto &rt: tree)
            for(auto &tr: rt -> children)
                nonRoot.insert(tr -> val);
        for(auto &rt: tree)
            if(!nonRoot.count(rt -> val))
                return rt;
        return nullptr;
    }
};
