class MedianFinder {
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int> > upp;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        for( ; !low.empty(); low.pop());
        for( ; !upp.empty(); upp.pop());
    }

    void addNum(int num) {
        if(upp.empty() || upp.top() <= num) {
            upp.push(num);
        } else {
            low.push(num);
        }
        if(low.size() > upp.size()) {
            upp.push(low.top());
            low.pop();
        } else if(upp.size() - low.size() > 1) {
            low.push(upp.top());
            upp.pop();
        }
    }

    double findMedian() {
        if(upp.empty())
            return 0.0;
        double ret = upp.top();
        if(upp.size() == low.size())
            ret = (ret + low.top()) / 2;
        return ret;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
