class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        int x[3], y[3];
        for(int i = 0; i < 3; ++i) {
            x[i] = points[i][0];
            y[i] = points[i][1];
        }
        for(int i = 1; i < 3; ++i) {
            x[i] -= x[0];
            y[i] -= y[0];
        }
        return x[1] * y[2] != x[2] * y[1];
    }
};
