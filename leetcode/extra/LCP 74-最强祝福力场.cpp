class Solution {
    typedef long long LL;
    void reduce(vector<LL> &seq) {
        sort(seq.begin(), seq.end());
        seq.erase(unique(seq.begin(), seq.end()), seq.end());
    }
    int locate(vector<LL> &seq, LL x) {
        return lower_bound(seq.begin(), seq.end(), x) - seq.begin();
    }
public:
    int fieldOfGreatestBlessing(vector<vector<int>>& seq) {
        vector<LL> queX, queY;
        for(auto &it: seq) {
            LL xM = it[0] * 2LL, yM = it[1] * 2LL, d = it[2];
            LL xL = xM - d, xR = xM + d + 1;
            LL yL = yM - d, yR = yM + d + 1;
            queX.push_back(xL);
            queX.push_back(xR);
            queY.push_back(yL);
            queY.push_back(yR);
        }
        reduce(queX);
        reduce(queY);
        int n = queX.size(), m = queY.size();
        vector<vector<int> > ctr(n, vector<int>(m));
        for(auto &it: seq) {
            LL xM = it[0] * 2LL, yM = it[1] * 2LL, d = it[2];
            int xL = locate(queX, xM - d);
            int xR = locate(queX, xM + d + 1);
            int yL = locate(queY, yM - d);
            int yR = locate(queY, yM + d + 1);
            ++ctr[xL][yL];
            --ctr[xL][yR];
            --ctr[xR][yL];
            ++ctr[xR][yR];
        }
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j)
                ctr[i][j] += ctr[i][j - 1];
        int ans = 0;
        for(int j = 0; j < m; ++j)
            ans = max(ans, ctr[0][j]);
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                ctr[i][j] += ctr[i - 1][j];
                ans = max(ans, ctr[i][j]);
            }
        return ans;
    }
};
