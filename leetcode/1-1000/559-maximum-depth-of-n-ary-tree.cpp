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
    int maxDepth(Node* root) {
        if(root == nullptr)
            return 0;
        int ret = 0;
        for(Node *nxt: root -> children)
            ret = max(ret, maxDepth(nxt));
        return ++ret;
    }
};
