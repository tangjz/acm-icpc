class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        static const int maxd = 10, maxl = 10, maxc = 5, maxm = 21;
        static int f[maxm][maxc | 1][maxl][maxm] = {}, pw[maxm][maxl] = {};
        if(!f[k][0][0][0]) {
            f[k][0][0][0] = 1;
            pw[k][0] = 1;
            for(int i = 1; i < maxl; ++i) {
                pw[k][i] = pw[k][i - 1] * maxd % k;
                for(int j = 0; j < maxc; ++j)
                    for(int r = 0; r < k; ++r)
                        for(int d = 0, rr = r; d < maxd; ++d, (rr -= pw[k][i - 1]) < 0 && (rr += k)) {
                            int jj = j - (d & 1);
                            if(jj >= 0)
                                f[k][j][i][r] += f[k][jj][i - 1][rr];
                        }
            }
        }
        auto calc = [&](int upp) {
            string s = to_string(upp);
            int ans = 0, len = s.size();
            if(!(len & 1))
                for(int i = 0, j = len >> 1, r = 0; i < len && j >= 0; ++i) {
                    int o = s[i] - '0';
                    for(int d = 0, rr = r; d < o; ++d, (rr -= pw[k][len - 1 - i]) < 0 && (rr += k)) {
                        if(!i && !d)
                            continue;
                        int jj = j - (d & 1);
                        if(jj >= 0)
                            ans += f[k][jj][len - 1 - i][rr];
                    }
                    j -= o & 1;
                    (r = (r - o * pw[k][len - 1 - i]) % k) < 0 && (r += k);
                }
            for(int i = 2; i < len; i += 2)
                for(int d = 0, r = 0; d < maxd; ++d, (r -= pw[k][i - 1]) < 0 && (r += k)) {
                    if(!d)
                        continue;
                    int j = (i >> 1) - (d & 1);
                    if(j >= 0)
                        ans += f[k][j][i - 1][r];
                }
            return ans;
        };
        return calc(high + 1) - calc(low);
    }
};
