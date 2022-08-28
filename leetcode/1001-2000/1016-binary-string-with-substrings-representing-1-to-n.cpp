class Solution {
public:
    bool queryString(string s, int n) {
        int m = s.size();
        vector<int> val(m);
        for(int i = 1; (1 << (i - 1)) <= n; ++i) {
            int L = 1 << (i - 1), R = min((1 << i) - 1, n);
            if(R - L + 1 > m - i + 1)
                return 0;
            int cnt = 0;
            vector<bool> vis(R - L + 1);
            for(int j = 0; j <= m - i; ++j) {
                val[j] = val[j] << 1 | (s[j + i - 1] == '1');
                if(val[j] >= L && val[j] <= R && !vis[val[j] - L]) {
                    vis[val[j] - L] = 1;
                    ++cnt;
                }
            }
            if(cnt < R - L + 1)
                return 0;
        }
        return 1;
    }
};
