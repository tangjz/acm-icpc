/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    Node *calc(int L, int R, string &s, unordered_map<int, int> &pR) {
        int pos = L;
        Node *ret = nullptr, *adt = nullptr, *tmp;
        if(s[pos] == '(') {
            adt = calc(pos + 1, pR[pos] - 1, s, pR);
            pos = pR[pos] + 1;
        } else {
            adt = new Node(s[pos++]);
        }
        while(pos <= R) {
            char op = s[pos++];
            if(s[pos] == '(') {
                tmp = calc(pos + 1, pR[pos] - 1, s, pR);
                pos = pR[pos] + 1;
            } else {
                tmp = new Node(s[pos++]);
            }
            switch(op) {
                case '+': case '-': {
                    (ret == nullptr ? ret : ret -> right) = adt;
                    ret = new Node(op, ret, nullptr);
                    adt = tmp;
                    break;
                }
                case '*': case '/': {
                    adt = new Node(op, adt, tmp);
                    break;
                }
            }
        }
        (ret == nullptr ? ret : ret -> right) = adt;
        return ret;
    }
public:
    Node* expTree(string s) {
        int n = s.size();
        unordered_map<int, int> pR;
        stack<int> stk;
        for(int i = 0; i < n; ++i)
            if(s[i] == '(') {
                stk.push(i);
            } else if(s[i] == ')') {
                pR[stk.top()] = i;
                stk.pop();
            }
        return calc(0, n - 1, s, pR);
    }
};
