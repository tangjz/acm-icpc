class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        static const int mod = 60;
        static int st = 0, tim[mod + 1] = {}, ctr[mod + 1] = {};
        if(!(++st)) {
            memset(tim, 0, sizeof tim);
            ++st;
        }
        int ans = 0;
        for(int x: time) {
            x %= mod;
            int y = x ? mod - x : 0;
            if(tim[y] == st)
                ans += ctr[y];
            if(tim[x] != st) {
                tim[x] = st;
                ctr[x] = 0;
            }
            ++ctr[x];
        }
        return ans;
    }
};
