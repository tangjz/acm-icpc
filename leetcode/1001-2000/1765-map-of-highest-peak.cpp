class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = (int)isWater.size();
        int m = (int)isWater[0].size();
        priority_queue<pair<int, pair<int, int> > > que;
        vector<vector<int> > height(n, vector<int>(m, -1));
        auto update = [&](int x, int y, int h) -> void {
            if(x < 0 || x >= n || y < 0 || y >= m || height[x][y] != -1)
                return;
            height[x][y] = h;
            que.push({-h, {x, y}});
        };
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(isWater[i][j]) {
                    update(i, j, 0);
                }
            }
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.top().second;
            que.pop();
            int h = height[x][y];
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy) {
                        continue;
                    }
                    update(x + dx, y + dy, h + 1);
                }
        }
        return height;
    }
};
