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
    Node* flipBinaryTree(Node* root, Node * leaf) {
        Node *ptr = leaf -> parent;
        if(ptr != nullptr) {
            if(leaf -> left != nullptr) {
                leaf -> right = leaf -> left;
                leaf -> left = nullptr;
            }
            leaf -> parent = nullptr;
            (ptr -> left == leaf ? ptr -> left : ptr -> right) = nullptr;
            ptr = flipBinaryTree(root, ptr);
            leaf -> left = ptr;
            ptr -> parent = leaf;
        }
        return leaf;
    }
};
