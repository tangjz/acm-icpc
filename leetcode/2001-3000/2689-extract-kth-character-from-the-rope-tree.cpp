/**
 * Definition for a rope tree node.
 * struct RopeTreeNode {
 *     int len;
 *     string val;
 *     RopeTreeNode *left;
 *     RopeTreeNode *right;
 *     RopeTreeNode() : len(0), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(string s) : len(0), val(std::move(s)), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x) : len(x), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x, RopeTreeNode *left, RopeTreeNode *right) : len(x), val(""), left(left), right(right) {}
 * };
 */
class Solution {
public:
    char getKthCharacter(RopeTreeNode* root, int k) {
        while(true) {
            if(!(root -> len))
                return (root -> val)[k - 1];
            RopeTreeNode *lch = root -> left;
            if(lch == nullptr) {
                root = root -> right;
                continue;
            }
            int leftLen = lch -> len;
            if(!leftLen)
                leftLen = (lch -> val).size();
            if(k <= leftLen) {
                root = lch;
            } else {
                root = root -> right;
                k -= leftLen;
            }
        }
        return '\0';
    }
};