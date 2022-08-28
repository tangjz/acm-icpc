class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& seg, vector<int>& que) {
        vector<int> idx;
        for(auto &it: seg) {
            idx.push_back(it[0]);
            idx.push_back(it[1] + 1);
        }
        for(int x: que)
            idx.push_back(x);
        sort(idx.begin(), idx.end());
        idx.erase(unique(idx.begin(), idx.end()), idx.end());
        int tot = (int)idx.size();
        vector<int> dsu(tot, -1), ans(tot, INT_MAX);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        sort(seg.begin(), seg.end(), [&](auto const &it, auto const &jt) {
            return it[1] - it[0] < jt[1] - jt[0];
        });
        for(auto &it: seg) {
            int len = it[1] - it[0] + 1;
            int L = lower_bound(idx.begin(), idx.end(), it[0]) - idx.begin();
            int R = lower_bound(idx.begin(), idx.end(), it[1] + 1) - idx.begin();
            for(int i = dsuFind(L); i < R; i = dsuFind(i)) {
                ans[i] = len;
                dsu[i] = dsuFind(i + 1);
            }
        }
        vector<int> ret;
        for(int x: que) {
            int pos = lower_bound(idx.begin(), idx.end(), x) - idx.begin();
            ret.push_back(ans[pos] < INT_MAX ? ans[pos] : -1);
        }
        return ret;
    }
};
