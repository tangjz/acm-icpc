class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        const int maxd = 3;
        int n = colors.size();
        vector<int> pos[maxd];
        for(int i = 0; i < n; ++i)
            pos[--colors[i]].push_back(i);
        vector<int> ret;
        ret.reserve(queries.size());
        for(auto &jt: queries) {
            int x = jt[0], c = --jt[1];
            if(pos[c].empty()) {
                ret.push_back(-1);
                continue;
            }
            int ans = INT_MAX;
            auto it = lower_bound(pos[c].begin(), pos[c].end(), x);
            if(it != pos[c].end())
                ans = min(ans, *it - x);
            if(it != pos[c].begin())
                ans = min(ans, x - *(--it));
            ret.push_back(ans);
        }
        return ret;
    }
};
