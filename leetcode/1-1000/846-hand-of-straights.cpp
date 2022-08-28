class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        unordered_map<int, int> ctr;
        for(int x : hand)
            ++ctr[x];
        auto get = [&](int x) {
            auto it = ctr.find(x);
            return it == ctr.end() ? 0 : it -> second;
        };
        vector<int> pos;
        for(int x : hand)
            if(!get(x - 1))
                pos.push_back(x);
        for(int x : pos) {
            if(!get(x))
                continue;
            int cur = x, nxt;
            while(cur != -1) {
                nxt = -1;
                int las = get(cur - 1);
                for(int i = 0; i < W; ++i) {
                    int rem = get(cur + i);
                    if(!rem)
                        return 0;
                    --ctr[cur + i];
                    --rem;
                    if(nxt == -1 && !las && rem)
                        nxt = cur + i;
                    las = rem;
                }
                if(nxt == -1 && !las && get(cur + W))
                    nxt = cur + W;
                cur = nxt;
            }
        }
        return 1;
    }
};
