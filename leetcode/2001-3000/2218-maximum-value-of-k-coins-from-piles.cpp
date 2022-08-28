class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int tot = 0;
        vector<int> f = {0};
        for(auto &it: piles) {
            int sz = it.size();
            vector<int> psum = {0};
            for(int x: it)
                psum.push_back(psum.back() + x);
            int nxt = min(tot + sz, k);
            f.resize(nxt + 1);
            for(int i = nxt; i > 0; --i)
                for(int j = max(1, i - tot); j <= sz && j <= i; ++j)
                    f[i] = max(f[i], f[i - j] + psum[j]);
            tot = nxt;
        }
        return f.size() == k + 1 ? f.back() : 0;
    }
};
