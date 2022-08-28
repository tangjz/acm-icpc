class Solution {
public:
    int superPow(int a, vector<int>& b) {
        const int mod = 1337;
        a %= mod;
        static int seq[mod], pos[mod], st = 0, tim[mod] = {};
        if(!(++st)) {
            memset(tim, 0, sizeof tim);
            ++st;
        }
        seq[0] = 1;
        pos[1] = 0;
        tim[1] = st;
        int len, per;
        for(int i = 1; ; ++i) {
            seq[i] = seq[i - 1] * a % mod;
            if(tim[seq[i]] == st) {
                len = pos[seq[i]];
                per = i - len;
                break;
            }
            tim[seq[i]] = st;
            pos[seq[i]] = i;
        }
        pair<int, bool> val = {};
        for(int x: b) {
            val.first = val.first * 10 + x;
            val.second |= val.first >= len;
            if(val.second)
                val.first = (val.first - len) % per + len;
        }
        return seq[val.first];
    }
};
