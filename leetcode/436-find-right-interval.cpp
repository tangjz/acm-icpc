class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = (int)intervals.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return intervals[u].front() < intervals[v].front();
        });
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            auto it = lower_bound(ord.begin(), ord.end(), intervals[i], [&](int const &u, vector<int> const &v) {
                return intervals[u].front() < v.back();
            });
            ret.push_back(it == ord.end() ? -1 : *it);
        }
        return ret;
    }
};
