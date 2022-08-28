class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int cnt = 0, low = INT_MAX;
        long long ans = 0;
        for(auto &it: matrix)
            for(int x: it) {
                int u = abs(x);
                ans += u;
                low = min(low, u);
                cnt += x < 0;
            }
        if(cnt & 1)
            ans -= low << 1;
        return ans;
    }
};
