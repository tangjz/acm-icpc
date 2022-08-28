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
    vector<int> postorder(Node* root) {
        if(root == nullptr)
            return {};
        vector<int> ret = {};
        for(Node *tr: root -> children) {
            vector<int> tmp = postorder(tr);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
        ret.push_back(root -> val);
        return ret;
    }
};
