class Solution {
public:
    int balancedString(string s) {
        const int maxd = 4;
        const char *pat = "QWER";
        int n = (int)s.size(), m = n / 4, cnt[maxd] = {}, ban = 0;
        for(char &ch : s)
            for(int i = 0; i < maxd; ++i)
                if(ch == pat[i]) {
                    ch = i;
                    ++cnt[ch];
                }
        for(int i = 0; i < maxd; ++i)
            ban += cnt[i] > m;
        int ans = n;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && ban > 0; ++j) {
                int o = s[j];
                ban -= cnt[o] > m;
                --cnt[o];
                ban += cnt[o] > m;
            }
            if(!ban)
                ans = min(ans, j - i);
            if(i < j) {
                int o = s[i];
                ban -= cnt[o] > m;
                ++cnt[o];
                ban += cnt[o] > m;
            } else {
                ++j;
            }
        }
        return ans;
    }
};
