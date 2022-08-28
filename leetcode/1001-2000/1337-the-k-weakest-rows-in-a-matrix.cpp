class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<int> cnt, pos;
        for(auto &it : mat) {
            int ctr = 0;
            for(int x : it)
                ctr += x != 0;
            cnt.push_back(ctr);
            pos.push_back(pos.empty() ? 0 : pos.back() + 1);
        }
        sort(pos.begin(), pos.end(), [&](int const &u, int const &v) {
            int dif = cnt[u] - cnt[v];
            return dif < 0 || (!dif && u < v);
        });
        pos.resize(k);
        return pos;
    }
};
