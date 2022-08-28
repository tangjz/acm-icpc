class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int f[2] = {INT_MAX, 0};
        for(int x: cost) {
            int g = min(f[0], f[1]) + x;
            f[0] = f[1];
            f[1] = g;
        }
        return min(f[0], f[1]);
    }
};
