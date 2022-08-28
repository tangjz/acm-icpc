class Solution {
public:
    int perfectMenu(vector<int>& upp, vector<vector<int>>& req, vector<vector<int>>& att, int lim) {
        int n = req.size(), m = upp.size();
        int ans = -1;
        for(int i = 0; i < (1 << n); ++i) {
            int c0 = 0, c1 = 0;
            vector<int> ctr(m);
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                c0 += att[j][0];
                c1 += att[j][1];
                for(int k = 0; k < m; ++k)
                    ctr[k] += req[j][k];
            }
            bool ban = c1 < lim;
            for(int j = 0; j < m; ++j)
                ban |= ctr[j] > upp[j];
            if(!ban)
                ans = max(ans, c0);
        }
        return ans;
    }
};
