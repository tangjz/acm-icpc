class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        auto calc = [&](int n, vector<int> &seq) {
            seq.push_back(1);
            seq.push_back(n);
            int m = seq.size();
            sort(seq.begin(), seq.end());
            vector<int> res;
            for(int i = 0; i < m; ++i)
                for(int j = 0; j < i; ++j)
                    res.push_back(seq[i] - seq[j]);
            sort(res.begin(), res.end());
            res.erase(unique(res.begin(), res.end()), res.end());
            // for(int x: res)
            //     printf("%d ", x);
            // puts("");
            return res;
        };
        vector<int> h = calc(m, hFences), v = calc(n, vFences);
        int ans = -1;
        for(auto it = h.begin(), jt = v.begin(); it != h.end() && jt != v.end(); ) {
            if(*it == *jt)
                ans = *it;
            if(*it < *jt) {
                ++it;
            } else {
                ++jt;
            }
        }
        const int mod = (int)1e9 + 7;
        return ans < 0 ? ans : 1LL * ans * ans % mod;
    }
};
