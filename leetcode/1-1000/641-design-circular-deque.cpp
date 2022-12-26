class MyCircularDeque {
    int cap, L, R;
    vector<int> que;
public:
    MyCircularDeque(int k) {
        cap = k;
        que.resize(cap + 1);
        L = R = 0;
    }

    bool insertFront(int value) {
        int nxtL = L - 1;
        nxtL < 0 && (nxtL = cap);
        if(nxtL == R)
            return 0;
        L = nxtL;
        que[L] = value;
        return 1;
    }

    bool insertLast(int value) {
        int nxtR = R + 1;
        nxtR > cap && (nxtR = 0);
        if(nxtR == L)
            return 0;
        que[R] = value;
        R = nxtR;
        return 1;
    }

    bool deleteFront() {
        if(L == R)
            return 0;
        (++L) > cap && (L = 0);
        return 1;
    }

    bool deleteLast() {
        if(L == R)
            return 0;
        (--R) < 0 && (R = cap);
        return 1;
    }

    int getFront() {
        if(L == R)
            return -1;
        return que[L];
    }

    int getRear() {
        if(L == R)
            return -1;
        int preR = R - 1;
        preR < 0 && (preR = cap);
        return que[preR];
    }

    bool isEmpty() {
        return L == R;
    }

    bool isFull() {
        int nxtR = R + 1;
        nxtR > cap && (nxtR = 0);
        return nxtR == L;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
