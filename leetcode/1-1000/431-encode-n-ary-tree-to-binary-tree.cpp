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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if(root == nullptr)
            return nullptr;
        TreeNode *rt = new TreeNode(root -> val), *cur = rt;
        for(Node *tr: root -> children)
            if(cur == rt) {
                cur -> left = encode(tr);
                cur = cur -> left;
            } else {
                cur -> right = encode(tr);
                cur = cur -> right;
            }
        return rt;
    }
	
    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if(root == nullptr)
            return nullptr;
        Node *rt = new Node(root -> val);
        if(root -> left != nullptr) {
            rt -> children.push_back(decode(root -> left));
            for(root = root -> left; root -> right != nullptr; root = root -> right)
                rt -> children.push_back(decode(root -> right));
        }
        return rt;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
