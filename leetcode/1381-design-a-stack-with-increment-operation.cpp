class CustomStack {
    int upp;
    vector<int> stk;
public:
    CustomStack(int maxSize) {
        upp = maxSize;
        vector<int>().swap(stk);
        stk.reserve(upp);
    }
    
    void push(int x) {
        if(stk.size() < upp)
            stk.push_back(x);
    }
    
    int pop() {
        int ret = -1;
        if(!stk.empty()) {
            ret = stk.back();
            stk.pop_back();
        }
        return ret;
    }
    
    void increment(int k, int val) {
        for(int &x : stk) {
            if(!k)
                break;
            x += val;
            --k;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
