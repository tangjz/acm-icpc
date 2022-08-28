class Solution {
public:
    string findContestMatch(int n) {
        int mx = 0;
        for( ; (1 << mx) < n; ++mx);
        vector<int> seq(n);
        for(int i = 2, j = n >> 1; i <= n; i <<= 1, j >>= 1)
            for(int k = j; k < n; k += j << 1)
                seq[k] = i - 1 - seq[k - j];
        string ret = "";
        for(int i = 0; i < n; ++i) {
            if(i > 0)
                ret.push_back(',');
            for(int c = i ? __builtin_ctz(i) : mx; c > 0; --c)
                ret.push_back('(');
            ret += to_string(seq[i] + 1);
            for(int c = ~i ? __builtin_ctz(~i) : mx; c > 0; --c)
                ret.push_back(')');
        }
        return ret;
    }
};
