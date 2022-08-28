class Solution {
public:
    vector<string> printKMoves(int K) {
        typedef unsigned int UL;
        typedef unsigned long long ULL;
        static const int maxd = 4, dx[maxd] = {0, 1, 0, -1}, dy[maxd] = {1, 0, -1, 0};
        static const char *dir = "RDLU";
        int x = 0, xL = 0, xR = 0;
        int y = 0, yL = 0, yR = 0;
        int d = 0;
        unordered_set<ULL> dark;
        while(K--) {
            ULL cur = (ULL)((UL)x) << 32 | (UL)y;
            if(dark.count(cur)) {
                dark.erase(cur);
                (--d) < 0 && (d = maxd - 1);
            } else {
                dark.insert(cur);
                (++d) == maxd && (d = 0);
            }
            x += dx[d];
            y += dy[d];
            if(x < xL) {
                xL = x;
            } else if(x > xR) {
                xR = x;
            }
            if(y < yL) {
                yL = y;
            } else if(y > yR) {
                yR = y;
            }
        }
        int xC = x, yC = y;
        int xLen = xR - xL + 1, yLen = yR - yL + 1;
        vector<string> ret(xLen);
        for(int x = xL; x <= xR; ++x) {
            ret[x - xL].reserve(yLen);
            for(int y = yL; y <= yR; ++y)
                if(x == xC && y == yC) {
                    ret[x - xL].push_back(dir[d]);
                } else {
                    ULL cur = (ULL)((UL)x) << 32 | (UL)y;
                    ret[x - xL].push_back("_X"[dark.count(cur)]);
                }
        }
        return ret;
    }
};
