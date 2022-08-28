class Solution {
    typedef long long i64;
    void to_string_rev(int &len, char buf[], i64 val, int base) {
        len = 0;
        if(!val) {
            buf[len++] = '0';
        }
        for( ; val > 0; buf[len++] = '0' + (val % base), val /= base);
        buf[len] = '\0';
    }
    bool is_par(int len, char buf[]) {
        for(int i = 0, j = len - 1; i < j; ++i, --j)
            if(buf[i] != buf[j])
                return false;
        return true;
    }
public:
    i64 kMirror(int k, int n) {
        int cnt = 0;
        i64 sum = 0;
        static int blen = 0;
        static char buf[21] = {};
        for(int len = 1; cnt < n; ++len) {
            i64 pw = 1;
            for(int i = 0; i < (len + 1) / 2; ++i)
                pw *= 10;
            for(i64 lft = pw / 10; cnt < n && lft < pw; ++lft) {
                i64 val = lft;
                if(len > 1) {
                    i64 pw2 = pw, tmp = lft;
                    if(len & 1) {
                        tmp /= 10;
                        pw2 /= 10;
                    }
                    to_string_rev(blen, buf, tmp, 10);
                    // i64 rht = stoi(a);
                    i64 rht = 0;
                    for(int j = 0; j < blen; ++j)
                        rht = rht * 10 + (buf[j] - '0');
                    val = val * pw2 + rht;
                }
                to_string_rev(blen, buf, val, k);
                if(is_par(blen, buf)) {
                    ++cnt;
                    sum += val;
                    // printf("%lld ", val);
                }
            }
        } // puts("");
        return sum;
    }
};
