class Solution {
public:
    int defendSpaceCity(vector<int>& time, vector<int>& position) {
        const int INF = 0x3f3f3f3f;
        int lowT = *min_element(time.begin(), time.end());
        int uppT = *max_element(time.begin(), time.end());
        int lowP = *min_element(position.begin(), position.end());
        int uppP = *max_element(position.begin(), position.end());
        int n = uppP - lowP + 1, m = uppT - lowT + 1;
        vector<int> msk(n);
        for(int i = 0; i < (int)time.size(); ++i) {
            int t = time[i] - lowT, p = position[i] - lowP;
            msk[p] |= 1 << t;
        }
        vector<int> f(1 << m, INF), bits(1 << m), seg(1 << m);
        for(int i = 1; i < (1 << m); ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
            seg[i] = seg[i >> 1] + ((i & 3) == 1);
        }
        f[0] = 0;
        for(int i = 0, las = 0, cur; i < n; ++i) {
            cur = msk[i];
            vector<int> g(1 << m, INF), h(1 << m, INF);
            for(int j = 0; j < (1 << m); ++j) {
                if(f[j] == INF)
                    continue;
                for(int k = 0; k < (1 << m); ++k) {
                    if((j & k) || ((j ^ k) & las) != las)
                        continue;
                    g[k] = min(g[k], f[j] + seg[k] * 2 + bits[k]);
                }
            }
            for(int j = 0; j < (1 << m); ++j) {
                if(g[j] == INF)
                    continue;
                for(int k = 0; k < (1 << m); ++k) {
                    if((k & j) != j)
                        continue;
                    int one = k ^ j;
                    h[k] = min(h[k], g[j] + seg[one] + bits[one]);
                }
            }
            f = move(h);
            las = cur;
        }
        int ans = INF;
        for(int i = 0, cur = msk.back(); i < (1 << m); ++i) {
            int one = cur & ~i;
            ans = min(ans, f[i] + seg[one] + bits[one]);
        }
        return ans;
    }
};
