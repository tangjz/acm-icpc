/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if(head == nullptr) {
            head = new Node(insertVal);
            head -> next = head;
        } else {
            for(Node *ptr = head; ; ptr = ptr -> next)
                if(ptr -> next == head || ((ptr -> next) -> val < ptr -> val && (ptr -> val <= insertVal || (ptr -> next) -> val > insertVal)) || (ptr -> val <= insertVal && (ptr -> next) -> val > insertVal)) {
                    ptr -> next = new Node(insertVal, ptr -> next);
                    break;
                }
        }
        return head;
    }
};
