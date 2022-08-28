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
            Node *ptr = root -> next;
            for( ; ptr != nullptr && ptr -> left == nullptr && ptr -> right == nullptr; ptr = ptr -> next);
            if(ptr != nullptr)
                ptr = ptr -> left != nullptr ? ptr -> left : ptr -> right;
            if(root -> right != nullptr) {
                root -> right -> next = ptr;
                ptr = root -> right;
            }
            if(root -> left != nullptr) {
                root -> left -> next = ptr;
            }
            root -> right = connect(root -> right);
            root -> left = connect(root -> left);
        }
        return root;
    }
};
