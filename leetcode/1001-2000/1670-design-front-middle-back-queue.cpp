class FrontMiddleBackQueue {
    deque<int> lft, rht;
public:
    FrontMiddleBackQueue() {
        deque<int>().swap(lft);
        deque<int>().swap(rht);
    }
    
    void pushFront(int val) {
        lft.push_front(val);
        while(lft.size() - 1 >= rht.size() + 1) {
            rht.push_front(lft.back());
            lft.pop_back();
        }
    }
    
    void pushMiddle(int val) {
        if(lft.size() > rht.size()) {
            rht.push_front(lft.back());
            lft.pop_back();
        }
        lft.push_back(val);
    }
    
    void pushBack(int val) {
        rht.push_back(val);
        while(lft.size() < rht.size()) {
            lft.push_back(rht.front());
            rht.pop_front();
        }
    }
    
    int popFront() {
        if(lft.empty())
            return -1;
        int ret = lft.front();
        lft.pop_front();
        while(lft.size() < rht.size()) {
            lft.push_back(rht.front());
            rht.pop_front();
        }
        return ret;
    }
    
    int popMiddle() {
        if(lft.empty())
            return -1;
        int ret = lft.back();
        lft.pop_back();
        while(lft.size() < rht.size()) {
            lft.push_back(rht.front());
            rht.pop_front();
        }
        return ret;
    }
    
    int popBack() {
        if(lft.empty())
            return -1;
        if(rht.empty()) {
            // size = 1
            return popFront();
        }
        int ret = rht.back();
        rht.pop_back();
        while(lft.size() - 1 >= rht.size() + 1) {
            rht.push_front(lft.back());
            lft.pop_back();
        }
        return ret;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
