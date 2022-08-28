class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int mx = 0;
        for(int x : nums)
            for( ; x >= (1 << mx); ++mx);
        int tot = 0;
        vector<int> ch[2], sz;
        auto newNode = [&]() {
            ch[0].push_back(0);
            ch[1].push_back(0);
            sz.push_back(0);
            return tot++;
        };
        assert(newNode() == 0);
        int ans = 0;
        auto calc = [&](int x, int upp) { // x xor y in [0, upp)
            int rt = 0;
            if((++upp) >= (1 << mx))
                return sz[rt];
            int cnt = 0;
            for(int i = mx - 1; i >= 0; --i) {
                int o = (x >> i) & 1, u = (upp >> i) & 1;
                if(!u) {
                    if(!ch[o][rt])
                        break;
                    rt = ch[o][rt];
                } else {
                    cnt += ch[o][rt] ? sz[ch[o][rt]] : 0;
                    if(!ch[!o][rt])
                        break;
                    rt = ch[!o][rt];
                }
            }
            return cnt;
        };
        for(int x : nums) {
            ans += calc(x, high) - calc(x, low - 1);
            int rt = 0;
            ++sz[rt];
            for(int i = mx - 1; i >= 0; --i) {
                int o = (x >> i) & 1;
                if(!ch[o][rt]) {
                    ch[o][rt] = newNode();
                }
                rt = ch[o][rt];
                ++sz[rt];
            }
        }
        return ans;
    }
};
