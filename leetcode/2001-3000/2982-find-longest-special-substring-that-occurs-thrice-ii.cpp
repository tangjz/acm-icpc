class Solution {
public:
    int maximumLength(string s) {
        const int maxd = 26;
        int n = s.size(), ans = -1;
        vector<vector<int> > sz(maxd);
        auto upd = [&](vector<int> &cand, int v) {
            for(int &x: cand)
                if(x < v)
                    swap(x, v);
            if(cand.size() < 3)
                cand.push_back(v);
            if(cand.size() == 3)
                ans = max(ans, cand.back());
        };
        for(int i = 0, j; i < n; ) {
            int o = s[i] - 'a';
            for(j = i; i < n && s[i] == s[j]; ++i)
                upd(sz[o], i - j + 1);
        }
        return ans;
    }
};
