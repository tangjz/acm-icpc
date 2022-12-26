class Solution {
public:
    string abbreviateProduct(int left, int right) {
        typedef long long LL;
        const LL maxv = (LL)1e10, mod = (LL)1e5;
        int c2 = 0, c5 = 0;
        double vD = 1;
        LL vL = 1, rem = 1;
        for(int i = left; i <= right; ++i) {
            int x = i;
            for( ; x % 2 == 0; x /= 2, ++c2);
            for( ; x % 5 == 0; x /= 5, ++c5);
            for(vD *= x; vD >= mod; vD /= 10);
            vL = min(vL * x, maxv);
            rem = rem * x % mod;
        }
        int ex = min(c2, c5);
        for(int i = ex; i < c2; ++i) {
            for(vD *= 2; vD >= mod; vD /= 10);
            vL = min(vL * 2, maxv);
            rem = rem * 2 % mod;
        }
        for(int i = ex; i < c5; ++i) {
            for(vD *= 5; vD >= mod; vD /= 10);
            vL = min(vL * 5, maxv);
            rem = rem * 5 % mod;
        }
        if(vL < maxv) {
            return to_string(vL) + "e" + to_string(ex);
        }
        string tmp = to_string(rem);
        while(tmp.size() < 5)
            tmp = "0" + tmp;
        return to_string((LL)floor(vD)) + "..." + tmp + "e" + to_string(ex);
    }
};
