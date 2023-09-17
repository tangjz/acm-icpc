class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int ans = 0;
        auto chk = [&](int x) -> bool {
            static const int maxv = (int)1e4 + 1, maxl = 7;
            static int res[maxv] = {};
            if(!res[x]) {
                static char buf[maxl];
                int len = sprintf(buf, "%d", x);
                if(len & 1) {
                    res[x] = -1;
                } else {
                    int s = 0;
                    for(int i = 0, j = len - 1; i < j; ++i, --j)
                        s += (int)buf[i] - (int)buf[j];
                    res[x] = s ? -1 : 1;
                }
            }
            return res[x] > 0;
        };
        for(int i = low; i <= high; ++i)
            ans += chk(i);
        return ans;
    }
};
