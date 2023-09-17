class Solution {
    typedef long long LL;
    LL calc(string &s) {
        int n = s.size();
        s.push_back('0');
        vector<int> pos;
        LL sum = 0;
        if(s[0] == '1') {
            pos.push_back(0);
            // printf("%d ", 0);
        }
        for(int i = 1; i <= n; ++i)
            if(s[i] != s[i - 1]) {
                pos.push_back(i);
                // printf("%d ", i);
                sum += i;
            }
        s.pop_back();
        // printf(": %s\n", s.c_str());
        int m = pos.size();
        assert(!(m & 1));
        LL ans = sum;
        for(int i = m - 2; i >= 0; i -= 2) {
            int u = pos[i], v = pos[i + 1];
            sum -= u + v;
            sum += n - u + n - v;
            // printf("%d: %lld\n", i, sum);
            ans = min(ans, sum);
        }
        // printf("%lld\n", ans);
        return ans;
    }
public:
    long long minimumCost(string s) {
        LL a = calc(s);
        for(char &ch: s)
            ch = '1' - ch + '0';
        return min(a, calc(s));
    }
};
