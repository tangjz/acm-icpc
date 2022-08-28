class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = min(n, 2);
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                int cnt = 0;
                int px = points[j][0] - points[i][0];
                int py = points[j][1] - points[i][1];
                for(int k = 0; k < n; ++k) {
                    if(k == i || k == j) {
                        ++cnt;
                        continue;
                    }
                    int qx = points[k][0] - points[i][0];
                    int qy = points[k][1] - points[i][1];
                    if(px * qy == qx * py)
                        ++cnt;
                }
                ans = max(ans, cnt);
            }
        return ans;
    }
};
