class Solution {
public:
    int longestAwesome(string s) {
        const int maxd = 10, maxs = 1 << maxd;
        vector<int> fir(maxs, -1);
        int ans = 0, n = (int)s.size(), msk = 0;
        for(int i = 0; i < n; ++i) {
            if(fir[msk] == -1)
                fir[msk] = i;
            int o = s[i] - '0';
            msk ^= 1 << o;
            if(fir[msk] != -1)
                ans = max(ans, i - fir[msk] + 1);
            for(int j = 0; j < maxd; ++j) {
                int tmp = msk ^ (1 << j);
                if(fir[tmp] != -1)
                    ans = max(ans, i - fir[tmp] + 1);
            }
        }
        return ans;
    }
};
