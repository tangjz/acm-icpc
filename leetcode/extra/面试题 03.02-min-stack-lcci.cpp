class MinStack {
private:
    stack<int> vals, upps;
public:
    /** initialize your data structure here. */
    MinStack() {
        stack<int>().swap(vals);
        stack<int>().swap(upps);
    }
    
    void push(int x) {
        vals.push(x);
        upps.push(upps.empty() ? x : min(x, upps.top()));
    }
    
    void pop() {
        vals.pop();
        upps.pop();
    }
    
    int top() {
        return vals.top();
    }
    
    int getMin() {
        return upps.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
