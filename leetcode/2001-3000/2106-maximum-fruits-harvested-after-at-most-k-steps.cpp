class Solution {
    int cost(int s, int L, int R) {
        if(s < L)
            return R - s;
        if(s > R)
            return s - L;
        return R - L + min(s - L, R - s);
    }
public:
    int maxTotalFruits(vector<vector<int>>& a, int s, int k) {
        int n = a.size(), ans = 0;
        for(int i = 0, j = 0, c = 0; i < n; c -= a[i++][1]) {
            for( ; j < n && cost(s, a[i][0], a[j][0]) <= k; c += a[j++][1]);
            ans = max(ans, c);
        }
        return ans;
    }
};
