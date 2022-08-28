class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        rotate(points.begin(), min_element(points.begin(), points.end()), points.end());
        auto det = [&](int u, int v, int w) {
            return (points[w][0] - points[v][0]) * (points[u][1] - points[v][1]) - (points[u][0] - points[v][0]) * (points[w][1] - points[v][1]);
        };
        if(det(n - 1, 0, 1) < 0)
            reverse(points.begin() + 1, points.end());
        for(int i = 1; i < n; ++i)
            if(det(i - 1, i, (i + 1) % n) < 0)
                return 0;
        return 1;
    }
};
