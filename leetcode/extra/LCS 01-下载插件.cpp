class Solution {
public:
    int leastMinutes(int n) {
        int mx = 0;
        for( ; (1 << mx) < n; ++mx);
        return mx + 1;
    }
};
