class Solution {
public:
    int numberOfSubstrings(string s) {
        int tot = 0;
        vector<int> ctr(3, 0);
        auto update = [&](int x, int v) {
            tot -= ctr[x] > 0;
            ctr[x] += v;
            tot += ctr[x] > 0;
        };
        int n = (int)s.size(), ans = 0;
        for(int L = 0, R = 0; L < n; ++L) {
            for( ; tot < 3 && R < n; ++R)
                update(s[R] - 'a', 1);
            if(tot == 3)
                ans += n - R + 1;
            update(s[L] - 'a', -1);
        }
        return ans;
    }
};
