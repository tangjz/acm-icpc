class Solution {
public:
    int minSideJumps(vector<int>& seq) {
        int f[3] = {INT_MAX, 0, INT_MAX};
        bool fir = 1;
        for(int x: seq) {
            if(!x) {
                int low = *min_element(f, f + 3);
                for(int j = 0; j < 3; ++j) {
                    f[j] = min(f[j], low + 1);
                }
                continue;
            }
            int g[3], low = INT_MAX;
            for(int j = 0; j < 3; ++j) {
                g[j] = j == x - 1 ? INT_MAX : f[j];
                low = min(low, g[j]);
            }
            for(int j = 0; j < 3; ++j) {
                f[j] = j == x - 1 ? INT_MAX : min(g[j], low + 1);
            }
        }
        return *min_element(f, f + 3);
    }
};
