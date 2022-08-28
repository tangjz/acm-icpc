class Solution {
public:
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {
        const int INF = 0x3f3f3f3f;
        int m = targetPath.size();
        unordered_map<string, int> Hash;
        vector<int> a(n), b(m);
        for(int i = 0; i < n; ++i) {
            auto it = Hash.find(names[i]);
            if(it != Hash.end()) {
                a[i] = it -> second;
            } else {
                a[i] = Hash.size();
                Hash.insert({names[i], a[i]});
            }
        }
        for(int i = 0; i < m; ++i) {
            auto it = Hash.find(targetPath[i]);
            if(it != Hash.end()) {
                b[i] = it -> second;
            } else {
                b[i] = Hash.size();
                Hash.insert({targetPath[i], b[i]});
            }
        }
        vector<vector<pair<int, int> > > dp(m, vector<pair<int, int> >(n, {INF, -1}));
        for(int i = 0; i < m; ++i) {
            if(!i) {
                for(int j = 0; j < n; ++j)
                    dp[i][j].first = 0;
            } else {
                for(auto &it: roads) {
                    int u = it[0], v = it[1];
                    if(dp[i][u].first > dp[i - 1][v].first)
                        dp[i][u] = {dp[i - 1][v].first, v};
                    if(dp[i][v].first > dp[i - 1][u].first)
                        dp[i][v] = {dp[i - 1][u].first, u};
                }
            }
            for(int j = 0; j < n; ++j)
                dp[i][j].first += b[i] != a[j];
        }
        vector<int> seq;
        seq.push_back(min_element(dp[m - 1].begin(), dp[m - 1].end()) - dp[m - 1].begin());
        for(int i = m - 1; i > 0; --i) {
            int j = seq.back();
            seq.push_back(dp[i][j].second);
        }
        reverse(seq.begin(), seq.end());
        return seq;
    }
};
