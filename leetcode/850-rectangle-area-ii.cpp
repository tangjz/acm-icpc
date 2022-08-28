class Solution {
public:
    int rectangleArea(vector<vector<int>>& recs) {
        vector<int> xque, yque;
        for(auto &it : recs) {
            xque.push_back(it[0]);
            yque.push_back(it[1]);
            xque.push_back(it[2]);
            yque.push_back(it[3]);
        }
        sort(xque.begin(), xque.end());
        xque.erase(unique(xque.begin(), xque.end()), xque.end());
        sort(yque.begin(), yque.end());
        yque.erase(unique(yque.begin(), yque.end()), yque.end());
        int n = (int)xque.size(), m = (int)yque.size();
        vector<vector<int> > ctr(n, vector<int>(m, 0));
        for(auto &it : recs) {
            int x0 = lower_bound(xque.begin(), xque.end(), it[0]) - xque.begin();
            int y0 = lower_bound(yque.begin(), yque.end(), it[1]) - yque.begin();
            int x1 = lower_bound(xque.begin(), xque.end(), it[2]) - xque.begin();
            int y1 = lower_bound(yque.begin(), yque.end(), it[3]) - yque.begin();
            ++ctr[x0][y0];
            --ctr[x0][y1];
            --ctr[x1][y0];
            ++ctr[x1][y1];
        }
        typedef long long LL;
        LL ans = 0;
        for(int i = 0; i < n - 1; ++i)
            for(int j = 0; j < m - 1; ++j)
                ctr[i][j + 1] += ctr[i][j];
        for(int i = 0; i < n - 1; ++i)
            for(int j = 0; j < m - 1; ++j) {
                if(!ctr[i][j])
                    continue;
                ans += (LL)(xque[i + 1] - xque[i]) * (yque[j + 1] - yque[j]);
                ctr[i + 1][j] += ctr[i][j];
            }
        return ans % ((int)1e9 + 7);
    }
};
