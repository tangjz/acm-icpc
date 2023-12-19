class Solution {
public:
    int countCompleteSubstrings(string buf, int k) {
        static const int maxc = 27, maxn = (int)1e5 + 1;
        int n = buf.size(), ans = 0;
        for(int c = 1, len = k; c < maxc && len <= n; ++c, len += k) {
            static int tot, bad, ctr[maxc];
            tot = bad = 0;
            memset(ctr, 0, sizeof ctr);
            for(int i = 0; i < n; ++i) {
                int o = buf[i] - 'a';
                tot += (++ctr[o]) == k;
                if(len > 1 && i > 0)
                    bad += abs(buf[i] - buf[i - 1]) > 2;
                if(i >= len - 1) {
                    ans += !bad && tot == c;
                    o = buf[i - len + 1] - 'a';
                    tot -= (ctr[o]--) == k;
                    if(len > 1)
                        bad -= abs(buf[i - len + 1] - buf[i - len + 2]) > 2;
                }
            }
        }
        return ans;
    }
};
