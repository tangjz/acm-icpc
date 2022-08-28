/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(root != nullptr) {
            root -> left = connect(root -> left);
            root -> right = connect(root -> right);
            Node *pL = root -> left, *pR = root -> right;
            while(pL != nullptr) {
                pL -> next = pR;
                pL = pL -> right;
                pR = pR != nullptr ? pR -> left : nullptr;
            }
        }
        return root;
    }
};
