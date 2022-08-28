class CQueue {
    stack<int> in, out;
public:
    CQueue() {
        stack<int>().swap(in);
        stack<int>().swap(out);
    }
    
    void appendTail(int value) {
        in.push(value);
    }
    
    int deleteHead() {
        if(out.empty())
            while(!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        if(out.empty())
            return -1;
        int ret = out.top();
        out.pop();
        return ret;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
