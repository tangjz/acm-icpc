class Solution {
    vector<vector<int> > const &dfs(int dep, int cnt, int sum) {
        static const int maxd = 10, maxs = 61;
        static bool vis[maxd + 1][maxd + 1][maxs];
        static vector<vector<int> > dp[maxd + 1][maxd + 1][maxs], none = {}, empty = {{}};
        if(!cnt && !sum)
            return empty;
        if(!dep || cnt < 0 || sum < 0)
            return none;
        if(!vis[dep][cnt][sum]) {
            auto &cur = dp[dep][cnt][sum];
            auto const &pre = dfs(dep - 1, cnt, sum);
            cur.insert(cur.end(), pre.begin(), pre.end());
            auto const &tmp = dfs(dep - 1, cnt - 1, sum - dep);
            for(auto const &it : tmp) {
                cur.push_back(it);
                cur.back().push_back(dep);
            }
            vis[dep][cnt][sum] = 1;
        }
        return dp[dep][cnt][sum];
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        static const int maxd = 10;
        return dfs(maxd - 1, k, n);
    }
};
