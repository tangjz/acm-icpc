class RateLimiter {
    int cap, dt;
    queue<int> que;
public:
    RateLimiter(int n, int t) {
        cap = n;
        dt = t;
        for( ; !que.empty(); que.pop());
    }

    bool shouldAllow(int timestamp) {
        for( ; !que.empty() && que.front() <= timestamp - dt; que.pop());
        if(que.size() < cap) {
            que.push(timestamp);
            return 1;
        }
        return 0;
    }
};
