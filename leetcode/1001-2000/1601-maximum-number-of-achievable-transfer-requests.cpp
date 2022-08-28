class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int m = (int)requests.size(), ans = 0;
        for(int i = 0; i < 1 << m; ++i) {
            int tot = 0;
            vector<int> deg(n);
            for(int j = 0; j < m; ++j)
                if((i >> j) & 1) {
                    ++tot;
                    ++deg[requests[j][0]];
                    --deg[requests[j][1]];
                }
            int pos;
            for(pos = 0; pos < n && !deg[pos]; ++pos);
            if(pos == n) {
                ans = max(ans, tot);
            }
        }
        return ans;
    }
};
