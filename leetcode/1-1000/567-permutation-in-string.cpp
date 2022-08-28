class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        const int maxd = 26;
        int n = (int)s1.length(), m = (int)s2.length();
        if(n > m)
            return 0;
        int cnt = maxd;
        vector<int> ctr(maxd, 0);
        auto upd = [&](int o, int v) {
            cnt -= !ctr[o];
            ctr[o] += v;
            cnt += !ctr[o];
        };
        for(char ch : s1)
            upd(ch - 'a', 1);
        int pos = 0;
        for(char ch : s2) {
            upd(ch - 'a', -1);
            if(pos >= n - 1) {
                if(pos >= n)
                    upd(s2[pos - n] - 'a', 1);
                if(cnt == maxd)
                    return 1;
            }
            ++pos;
        }
        return 0;
    }
};
