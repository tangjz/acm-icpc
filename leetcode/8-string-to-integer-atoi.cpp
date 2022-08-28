class Solution {
public:
    int myAtoi(string s) {
        typedef long long LL;
        int n = (int)s.size(), i = 0;
        LL v = 0;
        bool neg = false, ovf = false;
        for( ; i < n && s[i] == ' '; ++i);
        if(i < n && (s[i] == '-' || s[i] == '+')) {
            neg = s[i] == '-';
            ++i;
        }
        const LL INF = (1LL << 31) - !neg;
        for( ; i < n && s[i] >= '0' && s[i] <= '9'; ++i) {
            int x = s[i] - '0';
            v = min((v << 3) + (v << 1) + x, INF);
        }
        if(neg)
            v = -v;
        return (int)v;
    }
};
