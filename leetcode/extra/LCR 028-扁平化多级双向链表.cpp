/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if(head == NULL)
            return head;
        stack<Node *> stk;
        stk.push(head);
        while(!stk.empty()) {
            Node *cur = stk.top();
            stk.pop();
            if(cur -> next != NULL)
                stk.push(cur -> next);
            if(cur -> child != NULL) {
                Node *ch = cur -> child;
                cur -> next = ch;
                cur -> child = NULL;
                ch -> prev = cur;
                stk.push(ch);
            } else if(!stk.empty() && cur -> next == NULL) {
                Node *nxt = stk.top();
                cur -> next = nxt;
                nxt -> prev = cur;
            }
        }
        return head;
    }
};
