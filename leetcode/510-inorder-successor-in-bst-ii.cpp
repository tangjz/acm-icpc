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
    Node* inorderSuccessor(Node* node) {
        if(node -> right != nullptr) {
            node = node -> right;
            while(node -> left != nullptr)
                node = node -> left;
        } else {
            while(node -> parent != nullptr && node -> parent -> right == node)
                node = node -> parent;
            node = node -> parent;
        }
        return node;
    }
};
