class RecentCounter {
    queue<int> que;
public:
    RecentCounter() {
        while(!que.empty())
            que.pop();
    }
    
    int ping(int t) {
        que.push(t);
        while(!que.empty() && que.front() < t - 3000)
            que.pop();
        return que.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
