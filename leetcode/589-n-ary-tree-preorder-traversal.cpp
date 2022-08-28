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
    vector<int> preorder(Node* root) {
        if(root == nullptr)
            return {};
        vector<int> ret = {root -> val};
        for(Node *tr: root -> children) {
            vector<int> tmp = preorder(tr);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
        return ret;
    }
};
