class DataStream {
    int val, pos, dt;
    queue<int> cand;
public:
    DataStream(int value, int k) {
        val = value;
        pos = 0;
        dt = k;
    }

    bool consec(int num) {
        if(num == val)
            cand.push(pos);
        ++pos;
        while(!cand.empty() && pos - cand.front() > dt)
            cand.pop();
        return cand.size() == dt;
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */
