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
        if(root == nullptr)
            return nullptr;
        Node *lft = treeToDoublyList(root -> left), *rht = treeToDoublyList(root -> right), *tmp;
        root -> left = root -> right = root;
        if(lft != nullptr) {
            swap(root -> left -> right, lft -> left -> right);
            swap(root -> left, lft -> left);
            root = lft;
        }
        if(rht != nullptr) {
            swap(root -> left -> right, rht -> left -> right);
            swap(root -> left, rht -> left);
        }
        return root;
    }
};
