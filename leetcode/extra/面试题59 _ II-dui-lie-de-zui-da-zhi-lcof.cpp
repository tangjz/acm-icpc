class MaxQueue {
    int ctr;
    queue<pair<int, int> > que;
    deque<pair<int, int> > best;
public:
    MaxQueue() {
    }
    
    int max_value() {
        return que.empty() ? -1 : best.front().first;
    }
    
    void push_back(int value) {
        que.push({value, ++ctr});
        while(!best.empty() && best.back().first <= value)
            best.pop_back();
        best.push_back({value, ctr});
    }
    
    int pop_front() {
        if(que.empty())
            return -1;
        pair<int, int> cur = que.front();
        que.pop();
        if(best.front().second == cur.second)
            best.pop_front();
        return cur.first;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
