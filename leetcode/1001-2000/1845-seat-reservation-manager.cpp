class SeatManager {
    priority_queue<int> que;
public:
    SeatManager(int n) {
        while(!que.empty())
            que.pop();
        for(int i = 1; i <= n; ++i)
            que.push(-i);
    }
    
    int reserve() {
        int ret = -que.top();
        que.pop();
        return ret;
    }
    
    void unreserve(int seatNumber) {
        que.push(-seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
