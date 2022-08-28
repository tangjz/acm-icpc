class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int> > ret;
        for(int i = k; i <= n; ++i) {
            if(k == 1) {
                ret.push_back({i});
                continue;
            }
            vector<vector<int> > tmp = combine(i - 1, k - 1);
            for(auto &it: tmp) {
                it.push_back(i);
            }
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
        return move(ret);
    }
};
