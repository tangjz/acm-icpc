mt19937_64 rnd;

class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        const int maxn = 201;
        shuffle(circles.begin(), circles.end(), rnd);
        int ans = 0;
        for(int x = 0; x < maxn; ++x)
            for(int y = 0; y < maxn; ++y) {
                bool ok = 0;
                for(auto &it: circles) {
                    int dx = x - it[0];
                    int dy = y - it[1];
                    if(dx * dx + dy * dy <= it[2] * it[2]) {
                        ok = 1;
                        break;
                    }
                }
                ans += ok;
            }
        return ans;
    }
};
