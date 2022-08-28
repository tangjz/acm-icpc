class Solution {
public:
    int equalDigitFrequency(string s) {
        typedef long long LL;
        const int mod = (int)1e9 + 7, mod2 = (int)1e9 + 9, seed = 61, maxd = 10;
        int n = s.size();
        unordered_set<LL> ret;
        for(int i = 0; i < n; ++i) {
            int cnt = 0, msk = 0, upp = 0;
            int h0 = 0, h1 = 0;
            vector<int> ctr(maxd);
            for(int j = i; j < n; ++j) {
                int o = s[j] - '0' + 1;
                if(!((msk >> o) & 1)) {
                    msk |= 1 << o;
                    ++cnt;
                }
                upp = max(upp, ++ctr[o - 1]);
                h0 = ((LL)h0 * seed + o) % mod;
                h1 = ((LL)h1 * seed + o) % mod2;
                if(j - i + 1 == cnt * upp)
                    ret.insert((LL)h0 << 32 | h1);
            }
        }
        return ret.size();
    }
};
