class DinnerPlates {
    int cap;
    vector<vector<int> > seq;
    set<int> toAdd, toSub;

    void innerPush(int pos, int val) {
        // printf("push %d: %d\n", pos, val);
        auto &stk = seq[pos];
        if(stk.empty()) {
            toSub.insert(pos);
        }
        stk.push_back(val);
        if(stk.size() == cap) {
            toAdd.erase(pos);
        }
    }

    int innerPop(int pos) {
        auto &stk = seq[pos];
        int ret = stk.back();
        // printf("pop %d: %d\n", pos, ret);
        if(stk.size() == cap) {
            toAdd.insert(pos);
        }
        stk.pop_back();
        if(stk.empty()) {
            toSub.erase(pos);
        }
        return ret;
    }

public:
    DinnerPlates(int capacity) {
        cap = capacity;
        seq = {};
        toAdd = {};
        toSub = {};
    }

    void push(int val) {
        if(toAdd.empty()) {
            toAdd.insert(seq.size());
            seq.push_back({});
            seq.back().reserve(cap);
        }
        innerPush(*toAdd.begin(), val);
    }

    int pop() {
        if(toSub.empty())
            return -1;
        return innerPop(*toSub.rbegin());
    }

    int popAtStack(int index) {
        if(index >= seq.size() || seq[index].empty())
            return -1;
        return innerPop(index);
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */
