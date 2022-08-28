class Solution {
public:
    int countSpecialNumbers(int n) {
        static const int maxl = 11;
        static int ways[maxl][maxl] = {};
        if(!ways[0][0]) {
            for(int i = 0; i < maxl; ++i) {
                ways[i][0] = 1;
                for(int j = 1; j <= i; ++j)
                    ways[i][j] = ways[i][j - 1] * (i - j + 1);
            }
        }
        string buf = to_string(n + 1);
        int len = buf.size(), ans = 0;
        for(int i = 1; i < len; ++i)
            ans += ways[10][i] - ways[9][i - 1];
        for(int i = 0, msk = 0; i < len; ++i) {
            int d = buf[i] - '0';
            for(int j = !i; i < 10 && j < d; ++j) {
                if((msk >> j) & 1)
                    continue;
                ans += ways[10 - 1 - i][len - 1 - i];
            }
            if((msk >> d) & 1)
                break;
            msk |= 1 << d;
        }
        return ans;
    }
};
