class MyLinkedList {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(NULL) {}
        ListNode(int x) : val(x), next(NULL) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    } *head, *tail;
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = tail = NULL;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) const {
        ListNode *ptr = head;
        while(index--) {
            if(ptr == NULL)
                return -1;
            ptr = ptr -> next;
        }
        return ptr == NULL ? -1 : ptr -> val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ListNode *adt = new ListNode(val, head);
        head = adt;
        if(tail == NULL)
            tail = adt;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        ListNode *adt = new ListNode(val);
        if(head == NULL) {
            head = tail = adt;
        } else {
            tail -> next = adt;
            tail = adt;
        }
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index == 0) {
            addAtHead(val);
            return;
        }
        if(head == NULL)
            return;
        ListNode *las = head, *cur = las -> next;
        while(--index) {
            if(cur == NULL)
                return;
            las = cur;
            cur = las -> next;
        }
        if(cur == NULL) {
            addAtTail(val);
        } else {
            ListNode *adt = new ListNode(val, cur);
            las -> next = adt;
        }
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if(head == NULL)
            return;
        if(index == 0) {
            ListNode *nxt = head -> next;
            if(nxt == NULL) {
                head = tail = 0;
            } else {
                head = nxt;
            }
            return;
        }
        ListNode *las = head, *cur = las -> next;
        while(--index) {
            if(cur == NULL)
                return;
            las = cur;
            cur = las -> next;
        }
        if(cur == NULL)
            return;
        las -> next = cur -> next;
        if(cur == tail) {
            tail = las;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
