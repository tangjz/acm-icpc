class HitCounter {
    static const int maxd = 300;
    int tot;
    queue<pair<int, int> > que;
public:
    HitCounter() {
        tot = 0;
        for( ; !que.empty(); que.pop());
    }

    void hit(int timestamp) {
        while(!que.empty() && timestamp - que.front().first >= maxd) {
            tot -= que.front().second;
            que.pop();
        }
        if(que.empty() || que.back().first != timestamp) {
            que.push({timestamp, 1});
        } else {
            ++que.back().second;
        }
        ++tot;
    }

    int getHits(int timestamp) {
        while(!que.empty() && timestamp - que.front().first >= maxd) {
            tot -= que.front().second;
            que.pop();
        }
        return tot;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
