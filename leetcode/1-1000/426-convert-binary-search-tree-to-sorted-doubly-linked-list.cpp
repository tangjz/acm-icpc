/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(root != nullptr) {
            Node *pL = treeToDoublyList(root -> left);
            Node *pR = treeToDoublyList(root -> right);
            root -> left = root -> right = root;
            if(pL != nullptr) {
                Node *tail = pL -> left;
                tail -> right = root;
                pL -> left = root -> left;
                (root -> left) -> right = pL;
                root -> left = tail;
                root = pL;
            }
            if(pR != nullptr) {
                Node *tail = root -> left;
                tail -> right = pR;
                root -> left = pR -> left;
                (pR -> left) -> right = root;
                pR -> left = tail;
            }
        }
        return root;
    }
};
