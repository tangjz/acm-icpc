class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size(), ans = INT_MAX;
        set<pair<int, int> > Hash;
        for(auto &it: points)
            Hash.insert({it[0], it[1]});
        for(int i = 0; i < n; ++i) {
            int x0 = points[i][0], y0 = points[i][1];
            for(int j = i + 1; j < n; ++j) {
                int x1 = points[j][0], y1 = points[j][1];
                if(x0 != x1 && y0 != y1 && Hash.count({x0, y1}) && Hash.count({x1, y0})) {
                    ans = min(ans, abs(x0 - x1) * abs(y0 - y1));
                }
            }
        }
        return ans < INT_MAX ? ans : 0;
    }
};
