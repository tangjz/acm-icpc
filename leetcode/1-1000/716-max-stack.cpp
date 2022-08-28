class MaxStack {
    set<pair<int, int> > sp;
    stack<int> vals;
public:
    MaxStack() {
        stack<int>().swap(vals);
        sp.clear();
    }
    
    void push(int x) {
        sp.insert({x, vals.size()});
        vals.push(x);
    }
    
    int pop() {
        int x;
        do {
            x = vals.top();
            vals.pop();
        } while(!sp.erase({x, vals.size()}));
        return x;
    }
    
    int top() {
        while(!sp.count({vals.top(), vals.size() - 1}))
            vals.pop();
        return vals.top();
    }
    
    int peekMax() {
        return sp.rbegin() -> first;
    }
    
    int popMax() {
        pair<int, int> ret = *sp.rbegin();
        sp.erase(ret);
        return ret.first;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
