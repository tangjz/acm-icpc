class StackOfPlates {
    int cap, cnt, las, mx;
    vector<int> bits;
    vector<stack<int> > seq;

    int innerKth(int k) {
        int ret = 0;
        for(int i = 1 << (mx - 1), j; i > 0; i >>= 1) {
            j = ret | i;
            if(j > bits.size())
                continue;
            if(k + bits[j - 1] > cnt) {
                ret = j;
            } else {
                k += bits[j - 1];
            }
        }
        return ret - 1;
    }

    int innerPop(int idx) {
        int ret = seq[idx].top();
        seq[idx].pop();
        if(seq[idx].empty()) {
            --cnt;
            for(int x = idx + 1; x > 0; x -= x & -x)
                --bits[x - 1];
            if(cnt)
                las = innerKth(cnt);
        }
        return ret;
    }
    
public:
    StackOfPlates(int cap) {
        this -> cap = cap;
        cnt = mx = 0;
        las = -1;
        bits = {};
        seq = {};
    }
    
    void push(int val) {
        if(!cap)
            return;
        if(!cnt || seq[las].size() == cap) {
            ++cnt;
            seq.push_back({});
            bits.push_back(0);
            las = seq.size() - 1;
            mx += las + 1 == (1 << mx);
            for(int x = las + 1; x > 0; x -= x & -x)
                ++bits[x - 1];
        }
        seq[las].push(val);
    }
    
    int pop() {
        return cnt ? innerPop(las) : -1;
    }
    
    int popAt(int index) {
        return index < cnt ? innerPop(innerKth(index + 1)) : -1;
    }
};

/**
 * Your StackOfPlates object will be instantiated and called as such:
 * StackOfPlates* obj = new StackOfPlates(cap);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAt(index);
 */
