class MyCircularQueue {
    int n, p, c;
    vector<int> que;

    int tail() {
        int x = p + c - 1;
        return x < n ? x : (x - n);
    }
public:
    MyCircularQueue(int k) {
        n = k;
        p = c = 0;
        vector<int>(n).swap(que);
    }

    bool enQueue(int value) {
        if(c == n)
            return 0;
        ++c;
        que[tail()] = value;
        return 1;
    }

    bool deQueue() {
        if(!c)
            return 0;
        (++p) == n && (p = 0);
        --c;
        return 1;
    }

    int Front() {
        if(!c)
            return -1;
        return que[p];
    }

    int Rear() {
        if(!c)
            return -1;
        return que[tail()];
    }

    bool isEmpty() {
        return !c;
    }

    bool isFull() {
        return c == n;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
