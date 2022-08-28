class Solution {
public:
    int findKthNumber(int n, int k) {
        int len = to_string(++n).size();
        vector<int> pw(len);
        pw[0] = 1;
        for(int i = 1; i < len; ++i)
            pw[i] = pw[i - 1] * 10;
        int m = 0, len2 = 0;
        auto calc = [&]() -> int {
            if(len2 == len)
                return m < n;
            int ret = (pw[len - len2] - 1) / 9;
            int upp = n / pw[len - len2];
            if(m < upp) {
                ret += pw[len - len2];
            } else if(m == upp) {
                ret += n % pw[len - len2];
            }
            return ret;
        };
        for(len2 = 1; len2 <= len; ++len2) {
            int d = len2 == 1;
            m = m * 10 + d;
            for( ; d < 10; ++d, ++m) {
                int ways = calc();
                if(k <= ways)
                    break;
                k -= ways;
            }
            if(k == 1)
                break;
            --k;
        }
        return m;
    }
};
