class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        static const int maxd = 10, maxn = (int)1e4 + 1;
        static int com[maxd + 1][maxd + 1] = {};
        static int mx = 0, lcm[maxn] = {};
        static int tot = 0, seq[maxn] = {};
        if(!mx) {
            for(int i = 1; i < maxd; ++i)
                com[0][i] = i;
            for(int i = 1; i < maxd; ++i, ++mx) {
                for(int j = 0; j < maxd; ++j)
                    com[i][j] = i > j ? com[j][i] : com[i][j - i];
                lcm[i] = i;
                seq[tot++] = i;
            }
        }
        while(mx < right) {
            ++mx;
            int d = mx / maxd, r = mx % maxd;
            if(!lcm[d] || !r)
                continue;
            lcm[mx] = r / com[lcm[d] % r][r] * lcm[d];
            if(mx % lcm[mx] == 0)
                seq[tot++] = mx;
        }
        int L = lower_bound(seq, seq + tot, left) - seq;
        int R = lower_bound(seq, seq + tot, right + 1) - seq;
        return vector<int>(seq + L, seq + R);
    }
};
