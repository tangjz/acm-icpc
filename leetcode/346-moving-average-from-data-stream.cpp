class MovingAverage {
    int cnt, pos, sum;
    vector<int> que;
public:
    MovingAverage(int size) {
        cnt = pos = sum = 0;
        vector<int>(size).swap(que);
    }
    
    double next(int val) {
        sum -= que[pos];
        que[pos] = val;
        sum += que[pos];
        (++pos) == (int)que.size() && (pos = 0);
        cnt = min(cnt + 1, (int)que.size());
        return (double)sum / cnt;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
