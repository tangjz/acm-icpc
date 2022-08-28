class Solution {
    double getDistSum(vector<vector<int> > &p, double x, double y) {
        double ret = 0;
        for(auto &it : p) {
            double dx = x - it[0], dy = y - it[1];
            ret += sqrtl(dx * dx + dy * dy);
        }
        return ret;
    }
public:
    double getMinDistSum(vector<vector<int>>& p) {
        int xL = p[0][0], xR = xL;
        int yL = p[0][1], yR = yL;
        for(auto &it : p) {
            int x = it[0], y = it[1];
            xL = min(xL, x);
            xR = max(xR, x);
            yL = min(yL, y);
            yR = max(yR, y);
        }
        double x = (xL + xR) / 2.0, y = (yL + yR) / 2.0;
        double ans = getDistSum(p, x, y), delta = max((xR - xL) / 2.0, (yR - yL) / 2.0);
        const double eps = 1e-9, dec = 0.98;
        while(delta > eps) {
            bool upd = 1;
            while(upd) {
                upd = 0;
                const int maxd = 4, d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
                for(int i = 0; i < 4; ++i) {
                    double xx = x + delta * d[i][0], yy = y + delta * d[i][1];
                    double tmp = getDistSum(p, xx, yy);
                    if(ans > tmp) {
                        ans = tmp;
                        x = xx;
                        y = yy;
                        upd = 1;
                        break;
                    }
                }
            }
            delta *= dec;
        }
        return ans;
    }
};
