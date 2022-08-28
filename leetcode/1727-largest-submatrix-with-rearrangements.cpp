class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        int ans = 0;
        vector<int> h(m);
        for(auto &it : mat) {
            int tot = 0;
            map<int, int> ctr;
            for(int j = 0; j < m; ++j) {
                h[j] = it[j] ? h[j] + 1 : 0;
                if(h[j]) {
                    ++tot;
                    ++ctr[h[j]];
                }
            }
            for(auto &jt : ctr) {
                ans = max(ans, tot * jt.first);
                tot -= jt.second;
            }
        }
        return ans;
    }
};
