class Solution {
    typedef long long LL;
    pair<LL, LL> calc(string s) {
        int n = s.size(), pos = 0;
        LL num = 0, dom = 1, pw = 1;
        for( ; pos < n && s[pos] != '('; ++pos) {
            if(s[pos] == '.') {
                pw = 10;
                continue;
            }
            num = num * 10 + (s[pos] - '0');
            dom = dom * pw;
        }
        if(pos < n) {
            LL val = 0, pw = 0;
            for(++pos; pos < n && s[pos] != ')'; ++pos) {
                val = val * 10 + (s[pos] - '0');
                pw = pw * 10 + 9;
            }
            num = num * pw + val;
            dom *= pw;
        }
        LL com = gcd(num, dom);
        return {num / com, dom / com};
    }
public:
    bool isRationalEqual(string s, string t) {
        pair<LL, LL> a = calc(s), b = calc(t);
        return a == b;
    }
};
