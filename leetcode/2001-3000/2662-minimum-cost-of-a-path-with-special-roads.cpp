class Solution {
public:
    int minimumCost(vector<int>& s, vector<int>& t, vector<vector<int>>& e) {
        int ans = INT_MAX;
        vector<pair<int, int> > seq;
        seq.push_back({s[0], s[1]});
        seq.push_back({t[0], t[1]});
        for(auto &it: e) {
            seq.push_back({it[0], it[1]});
            seq.push_back({it[2], it[3]});
        }
        sort(seq.begin(), seq.end());
        seq.erase(unique(seq.begin(), seq.end()), seq.end());
        int n = seq.size();
        // printf("n %d\n", n);
        // for(int i = 0; i < n; ++i)
        //     printf("%d %d\n", seq[i].first, seq[i].second);
        static const int maxn = 409;
        static int dis[maxn][maxn];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dis[i][j] = abs(seq[i].first - seq[j].first) + abs(seq[i].second - seq[j].second);
        auto getID = [&](pair<int, int> const &v) -> int {
            // printf("ask %d %d\n", v.first, v.second);
            return lower_bound(seq.begin(), seq.end(), v) - seq.begin();
        };
        for(auto &it: e) {
            int u = getID({it[0], it[1]});
            int v = getID({it[2], it[3]});
            // printf("u %d v %d\n", u, v);
            dis[u][v] = min(dis[u][v], it[4]);
            // printf("dis[u][v] %d\n", dis[u][v]);
        }
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        return dis[getID({s[0], s[1]})][getID({t[0], t[1]})];
    }
};
