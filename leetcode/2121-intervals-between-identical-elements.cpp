class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        typedef long long LL;
        int n = arr.size();
        unordered_map<int, vector<int> > hs;
        for(int i = 0; i < n; ++i)
            hs[arr[i]].push_back(i);
        vector<LL> ret(n);
        for(auto &it: hs) {
            auto &pos = it.second;
            int m = pos.size();
            LL lft = 0, rht = 0;
            for(int x: pos)
                rht += x;
            for(int i = 0; i < m; ++i) {
                ret[pos[i]] = rht - (m - i) * (LL)pos[i] + i * (LL)pos[i] - lft;
                rht -= pos[i];
                lft += pos[i];
            }
        }
        return ret;
    }
};
