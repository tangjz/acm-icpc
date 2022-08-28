class Solution {
private:
    static const int maxl = 11, maxv = 9 * 9 * 9 + 2;
    int getNext(int n) { // if n > 0, then result < maxv
        static char buf[maxl];
        int ret = 0, len = sprintf(buf, "%d", n);
        for(int i = 0; i < len; ++i) {
            int x = buf[i] - '0';
            ret += x * x;
        }
        return ret;
    }
public:
    bool isHappy(int n) {
        if(n <= 1)
            return n == 1;
        static int tim = 0, vis[maxv] = {};
        ++tim;
        for(int m = getNext(n); m != 1; m = getNext(m))
            if(vis[m] == tim) {
                return 0;
            } else {
                vis[m] = tim;
            }
        return 1;
    }
};
