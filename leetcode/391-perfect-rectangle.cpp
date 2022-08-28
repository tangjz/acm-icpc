class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        typedef unsigned long long ULL;
        unordered_set<ULL> Hash;
        auto upd = [&](int x, int y) {
            ULL msk = (ULL)x << 32 | (ULL)y;
            if(!Hash.insert(msk).second)
                Hash.erase(msk);
        };
        int sum = 0;
        int xL = INT_MAX, xR = INT_MIN;
        int yL = xL, yR = xR;
        for(auto &it : rectangles) {
            int x0, y0, x1, y1;
            tie(x0, y0, x1, y1) = tie(it[0], it[1], it[2], it[3]);
            sum += (x1 - x0) * (y1 - y0);
            xL = min(xL, x0);
            yL = min(yL, y0);
            xR = max(xR, x1);
            yR = max(yR, y1);
            upd(x0, y0);
            upd(x0, y1);
            upd(x1, y0);
            upd(x1, y1);
        }
        upd(xL, yL);
        upd(xL, yR);
        upd(xR, yL);
        upd(xR, yR);
        return sum == (xR - xL) * (yR - yL) && Hash.empty();
    }
};
