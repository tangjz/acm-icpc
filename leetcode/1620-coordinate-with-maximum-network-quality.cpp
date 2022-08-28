class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        const int maxv = 50;
        int ans = -1, px = -maxv - 1, py = -maxv - 1;
        for(int x = 0; x <= maxv + maxv; ++x)
            for(int y = 0; y <= maxv + maxv; ++y) {
                int tmp = 0;
                for(auto &it: towers) {
                    int dx = it[0] - x, dy = it[1] - y;
                    int dis2 = dx * dx + dy * dy;
                    if(dis2 > radius * radius)
                        continue;
                    tmp += floor(it[2] / (1 + sqrtl(dis2)));
                }
                if(ans < tmp) {
                    ans = tmp;
                    px = x;
                    py = y;
                }
            }
        return {px, py};
    }
};
