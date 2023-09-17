class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        typedef long long LL;
        static const int maxl = 23, maxs = 209, maxd = 10, mod = (int)1e9 + 7;
        if(min_sum >= maxs)
            return 0;
        auto modInc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        auto modDec = [&](int &x, int y) {
            (x -= y) < 0 && (x += mod);
        };
        static int f[maxl][maxs] = {};
        if(!f[0][0]) {
            f[0][0] = 1;
            for(int i = 1; i < maxl; ++i)
                for(int j = 0; j < maxs; ++j) {
                    if(!f[i - 1][j])
                        continue;
                    for(int d = 0; d < maxd && j + d < maxs; ++d)
                        modInc(f[i][j + d], f[i - 1][j]);
                }
            for(int i = 0; i < maxl; ++i)
                for(int j = 1; j < maxs; ++j)
                    modInc(f[i][j], f[i][j - 1]);
        }
        auto calc = [&](string s, int upp) {
            int n = s.size(), res = 0, cur = 0;
            upp = min(upp, n * (maxd - 1));
            for(int i = 0; i < n && cur < upp; ++i) {
                int d = s[i] - '0';
                for(int j = 0; j < d && cur + j < upp; ++j)
                    modInc(res, f[n - 1 - i][upp - 1 - cur - j]);
                cur += d;
            }
            return res;
        };
        reverse(num2.begin(), num2.end());
        num2.push_back('0');
        ++num2.front();
        for(int i = 0; num2[i] > '9'; ++i) {
            num2[i] -= 10;
            ++num2[i + 1];
        }
        if(num2.back() == '0')
            num2.pop_back();
        reverse(num2.begin(), num2.end());
        int res = calc(num2, max_sum + 1);
        modDec(res, calc(num1, max_sum + 1));
        modDec(res, calc(num2, min_sum));
        modInc(res, calc(num1, min_sum));
        return res;
    }
};
