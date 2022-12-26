class TripleInOne {
    int cap, sz[3];
    vector<int> seq;
public:
    TripleInOne(int stackSize) {
        cap = stackSize;
        sz[0] = sz[1] = sz[2] = 0;
        seq.resize(cap * 3);
    }

    void push(int stackNum, int value) {
        if(sz[stackNum] == cap)
            return;
        seq[stackNum * cap + (sz[stackNum]++)] = value;
    }

    int pop(int stackNum) {
        return !sz[stackNum] ? -1 : seq[stackNum * cap + (--sz[stackNum])];
    }

    int peek(int stackNum) {
        return !sz[stackNum] ? -1 : seq[stackNum * cap + sz[stackNum] - 1];
    }

    bool isEmpty(int stackNum) {
        return !sz[stackNum];
    }
};

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */
