class Solution {
public:
    int magicalString(int n) {
        static const int maxn = (int)1e5 + 1;
        static int ctr[maxn] = {};
        static char buf[maxn] = {};
        if(!buf[0]) {
            char ch = '1';
            buf[0] = '1';
            buf[1] = '2';
            buf[2] = '2';
            for(int i = 3, j = 2; i < maxn; ++j, ch = '2' - ch + '1') {
                buf[i++] = ch;
                if(i < maxn && buf[j] == '2')
                    buf[i++] = ch;
            }
            for(int i = 1; i < maxn; ++i)
                ctr[i] = ctr[i - 1] + (buf[i - 1] == '1');
        }
        return ctr[n];
    }
};
