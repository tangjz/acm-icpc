/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node *ptr;
        vector<Node *> lft, rht;
        for(ptr = p; ptr != nullptr; ptr = ptr -> parent)
            lft.push_back(ptr);
        for(ptr = q; ptr != nullptr; ptr = ptr -> parent)
            rht.push_back(ptr);
        while(!lft.empty() && !rht.empty() && lft.back() == rht.back()) {
            ptr = lft.back();
            lft.pop_back();
            rht.pop_back();
        }
        return ptr;
    }
};
