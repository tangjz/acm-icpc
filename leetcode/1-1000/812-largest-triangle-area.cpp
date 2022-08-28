class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                for(int k = j + 1; k < n; ++k) {
                    int x0 = points[j][0] - points[i][0];
                    int y0 = points[j][1] - points[i][1];
                    int x1 = points[k][0] - points[i][0];
                    int y1 = points[k][1] - points[i][1];
                    ans = max(ans, abs(x0 * y1 - x1 * y0));
                }
        return ans * 0.5;
    }
};
