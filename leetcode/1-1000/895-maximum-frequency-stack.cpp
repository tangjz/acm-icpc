class FreqStack {
    int counter;
    map<int, int> times;
    priority_queue<pair<int, pair<int, int> > > queue;
public:
    FreqStack() {
        counter = 0;
        map<int, int>().swap(times);
        for( ; !queue.empty(); queue.pop());
    }
    
    void push(int x) {
        queue.push(make_pair(++times[x], make_pair(++counter, x)));
    }
    
    int pop() {
        int ret = queue.top().second.second;
        queue.pop();
        --times[ret];
        return ret;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack obj = new FreqStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 */
