class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size(), ans = 0;
        vector<pair<int, int> > ctr(n + 1);
        vector<int> ret(n);
        auto upd = [&](int x, pair<int, int> v) {
            ans -= min(ctr[x].first, ctr[x].second);
            ctr[x] = {ctr[x].first + v.first, ctr[x].second + v.second};
            ans += min(ctr[x].first, ctr[x].second);
        };
        for(int i = 0; i < n; ++i) {
            upd(A[i], {1, 0});
            upd(B[i], {0, 1});
            ret[i] = ans;
        }
        return ret;
    }
};
