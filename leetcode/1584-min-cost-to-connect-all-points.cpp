class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& p) {
        int ans = 0, n = (int)p.size();
        vector<int> dis(n, INT_MAX);
        auto dist = [&](int x0, int y0, int x1, int y1) {
            return abs(x0 - x1) + abs(y0 - y1);
        };
        for(int i = 1; i < n; ++i)
            dis[i] = dist(p[0][0], p[0][1], p[i][0], p[i][1]);
        for(int i = 1; i < n; ++i) {
            int pos = min_element(dis.begin(), dis.end()) - dis.begin();
            ans += dis[pos];
            dis[pos] = INT_MAX;
            for(int j = 0; j < n; ++j)
                if(dis[j] != INT_MAX)
                    dis[j] = min(dis[j], dist(p[pos][0], p[pos][1], p[j][0], p[j][1]));
        }
        return ans;
    }
};
