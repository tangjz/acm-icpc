class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string buf = to_string(n + 1);
        int len = buf.size(), ans = n;
        for(int i = 1, ways = 1; i < len; ++i) {
            ways *= i > 1 ? 11 - i : 10 - i;
            ans -= ways;
        }
        for(int i = 0, msk = 0; i < len; ++i) {
            int val = buf[i] - '0', ways = 0;
            for(int j = i > 0 ? 0 : 1; j < val; ++j) {
                if((msk >> j) & 1)
                    continue;
                ++ways;
            }
            if(ways) {
                for(int j = i + 1; j < len; ++j)
                    ways *= 10 - j;
                ans -= ways;
            }
            if((msk >> val) & 1)
                break;
            msk |= 1 << val;
        }
        return ans;
    }
};
