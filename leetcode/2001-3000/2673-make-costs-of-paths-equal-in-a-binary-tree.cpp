class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        int ans = 0;
        for(int i = n / 2; i > 0; --i) {
            int u = cost[i + i - 1], v = cost[i + i];
            ans += abs(u - v);
            cost[i - 1] += max(u, v);
        }
        return ans;
    }
};
