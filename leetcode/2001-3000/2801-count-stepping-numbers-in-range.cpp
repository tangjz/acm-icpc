class Solution {
public:
    int countSteppingNumbers(string low, string high) {
        static const int mod = (int)1e9 + 7, maxd = 10, maxn = 109;
        typedef long long LL;
        static int f[maxd][maxn] = {};
        if(!f[0][0]) {
            for(int i = 0; i < maxd; ++i)
                f[i][0] = 1;
            for(int i = 1; i < maxn; ++i)
                for(int j = 0; j < maxd; ++j) {
                    f[j][i] = (j > 0 ? f[j - 1][i - 1] : 0) + (j + 1 < maxd ? f[j + 1][i - 1] : 0);
                    f[j][i] >= mod && (f[j][i] -= mod);
                }
        }
        auto inc = [&](string &s) {
            int n = s.size(), i = n - 1;
            for(++s[i]; i > 0 && s[i] > '9'; ++s[i - 1], s[i] -= 10, --i);
            if(s[i] > '9') { // i = 0
                s[0] -= 10;
                s.insert(s.begin(), '1');
            }
        };
        inc(high);
        auto calc = [&](string &s) {
            int n = s.size(), ret = 0;
            bool ban = 0;
            for(int i = 0, las, cur; i < n; ++i) {
                cur = s[i] - '0';
                if(!ban)
                    for(int j = !i; j < cur; ++j)
                        if(!i || abs(las - j) == 1)
                            (ret += f[j][n - 1 - i]) >= mod && (ret -= mod);
                if(i > 0)
                    for(int j = 1; j < maxd; ++j)
                        (ret += f[j][n - 1 - i]) >= mod && (ret -= mod);
                ban |= i > 0 && abs(las - cur) != 1;
                las = cur;
            }
            return ret;
        };
        int ans = calc(high) - calc(low);
        ans < 0 && (ans += mod);
        return ans;
    }
};
