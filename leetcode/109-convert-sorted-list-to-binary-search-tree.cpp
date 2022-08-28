/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<TreeNode *> seq;
        for( ; head != nullptr; head = head -> next)
            seq.push_back(new TreeNode(head -> val));
        function<TreeNode *(int, int)> build = [&](int L, int R) -> TreeNode* {
            if(L > R)
                return nullptr;
            int M = (L + R) >> 1;
            seq[M] -> left = build(L, M - 1);
            seq[M] -> right = build(M + 1, R);
            return seq[M];
        };
        return build(0, (int)seq.size() - 1);
    }
};
