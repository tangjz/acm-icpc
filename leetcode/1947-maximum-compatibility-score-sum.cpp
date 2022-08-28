class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int m = students.size(), n = students[0].size();
        vector<vector<int> > scores(m, vector<int>(m));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j)
                for(int k = 0; k < n; ++k)
                    scores[i][j] += students[i][k] == mentors[j][k];
        vector<pair<int, int> > dp(1 << m);
        for(int i = 0; i < (1 << m); ++i) {
            if(i > 0)
                dp[i].second = dp[i >> 1].second + (i & 1);
            for(int j = 0; j < m; ++j) {
                if((i >> j) & 1)
                    continue;
                int nxt = i | (1 << j);
                dp[nxt].first = max(dp[nxt].first, dp[i].first + scores[dp[i].second][j]);
            }
        }
        return dp.back().first;
    }
};
