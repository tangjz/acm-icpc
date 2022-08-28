class MRUQueue {
    int mx;
    vector<int> que, bits;
public:
    MRUQueue(int n) {
        const int maxd = 2000;
        que.resize(n + 1);
        iota(que.begin(), que.end(), 0);
        que.reserve(n + maxd + 1);
        bits.resize(n + maxd + 1);
        for(int i = 1, j; i <= n + maxd; ++i) {
            if(i <= n)
                ++bits[i];
            j = i + (i & -i);
            if(j <= n + maxd)
                bits[j] += bits[i];
        }
        for(mx = 1; (mx << 1) <= n + maxd; mx <<= 1);
    }
    
    int fetch(int k) {
        int pos = 0;
        for(int i = mx, nxt; i > 0; i >>= 1) {
            nxt = pos | i;
            if(nxt < bits.size() && bits[nxt] < k) {
                pos = nxt;
                k -= bits[nxt];
            }
        }
        que.push_back(que[++pos]);
        for(int i = pos; i < bits.size(); i += i & -i)
            --bits[i];
        for(int i = que.size() - 1; i < bits.size(); i += i & -i)
            ++bits[i];
        return que.back();
    }
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */
