class Solution {
public:
    int minDayskVariants(vector<vector<int>>& points, int k) {
        int n = points.size();
        int xL = INT_MAX, xR = INT_MIN;
        int yL = INT_MAX, yR = INT_MIN;
        vector<int> dis(n);
        for(int i = 0; i < n; ++i) {
            int x = points[i][0];
            int y = points[i][1];
            xL = min(xL, x);
            xR = max(xR, x);
            yL = min(yL, y);
            yR = max(yR, y);
        }
        int ans = INT_MAX;
        for(int x = xL; x <= xR; ++x)
            for(int y = yL; y <= yR; ++y) {
                for(int i = 0; i < n; ++i)
                    dis[i] = abs(x - points[i][0]) + abs(y - points[i][1]);
                nth_element(dis.begin(), dis.begin() + (k - 1), dis.end());
                ans = min(ans, dis[k - 1]);
            }
        return ans;
    }
};
