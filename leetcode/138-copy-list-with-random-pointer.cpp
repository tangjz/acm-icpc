/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr)
            return nullptr;
        unordered_map<Node *, Node *> Hash;
        Node *newHead = new Node(head -> val);
        for(Node *p = head, *q = newHead; p != nullptr; p = p -> next, q = q -> next) {
            Hash.insert({p, q});
            if(p -> next != nullptr) {
                q -> next = new Node(p -> next -> val);
            }
            q -> random = p -> random;
        }
        for(Node *p = newHead; p != nullptr; p = p -> next)
            p -> random = Hash[p -> random];
        return newHead;
    }
};
