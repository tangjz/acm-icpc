class Solution {
public:
    vector<vector<int>> findMaximalUncoveredRanges(int n, vector<vector<int>>& seg) {
        seg.push_back({n, n});
        int m = seg.size();
        sort(seg.begin(), seg.end(), [&](auto const &u, auto const &v) {
            return u[0] < v[0];
        });
        int sz = 0;
        for(int i = 0; i < m; ++i)
            if(sz && seg[i][0] <= seg[sz - 1][1]) {
                seg[sz - 1][1] = max(seg[sz - 1][1], seg[i][1]);
            } else {
                seg[sz++] = seg[i];
            }
        m = 0;
        int las = -1, cur;
        for(int i = 0; i < sz && las < n - 1; ++i) {
            cur = seg[i][1];
            if(seg[i][0] > las + 1)
                seg[m++] = {las + 1, seg[i][0] - 1};
            las = cur;
        }
        if(m && seg[m - 1][1] >= n)
            seg[m - 1][1] = n - 1;
        seg.resize(m);
        return seg;
    }
};