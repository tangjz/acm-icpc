class Skiplist {
    mt19937 rnd;
    class Node {
    public:
        int value;
        vector<Node *> next;
    } *head;
public:
    Skiplist() {
        rnd.seed(time(nullptr));
        head = new Node();
        (head -> next).resize(1);
    }

    void print() {
        for(int dep = (int)(head -> next).size() - 1; dep >= 0; --dep) {
            printf("dep %d:", dep);
            for(Node *ptr = (head -> next)[dep]; ptr != nullptr; ptr = (ptr -> next)[dep])
                printf(" %d", ptr -> value);
            puts("");
        }
    }

    bool search(int target) {
        // print();
        Node *ptr = head, *tmp;
        for(int dep = (int)(ptr -> next).size() - 1; dep >= 0; --dep)
            while(true) {
                tmp = (ptr -> next)[dep];
                if(tmp != nullptr && tmp -> value < target) {
                    ptr = tmp;
                } else {
                    break;
                }
            }
        return tmp != nullptr && tmp -> value == target;
    }

    void add(int num) {
        // print();
        int upp = 1;
        while(rnd() & 1)
            ++upp;
        Node *ptr = head, *cur = new Node(), *tmp;
        if((ptr -> next).size() < upp)
            (ptr -> next).resize(upp);
        cur -> value = num;
        (cur -> next).resize(upp);
        for(int dep = (int)(ptr -> next).size() - 1; dep >= 0; --dep) {
            while(true) {
                tmp = (ptr -> next)[dep];
                if(tmp != nullptr && tmp -> value < num) {
                    ptr = tmp;
                } else {
                    break;
                }
            }
            if(dep < upp) {
                (cur -> next)[dep] = tmp;
                (ptr -> next)[dep] = cur;
            }
        }
    }

    bool erase(int num) {
        // print();
        Node *ptr = head, *tmp;
        bool found = false;
        for(int dep = (int)(ptr -> next).size() - 1; dep >= 0; --dep) {
            while(true) {
                tmp = (ptr -> next)[dep];
                if(tmp != nullptr && tmp -> value < num) {
                    ptr = tmp;
                } else {
                    break;
                }
            }
            if(tmp != nullptr && tmp -> value == num) {
                found = true;
                (ptr -> next)[dep] = ((ptr -> next)[dep] -> next)[dep];
                if(dep > 0 && (head -> next)[dep] == nullptr)
                    (head -> next).pop_back();
            }
        }
        return found;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
