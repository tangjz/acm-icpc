class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        unordered_map<int, int> ctr;
        for(int x: candidates)
            ++ctr[x];
        vector<pair<int, int> > seq;
        for(auto &it: ctr)
            seq.push_back(it);
        int n = seq.size();
        vector<vector<bool> > dp(n + 1, vector<bool>(target + 1));
        dp[0][0] = 1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= target; ++j) if(dp[i][j])
                for(int k = 0, jj = j; k <= seq[i].second && jj <= target; ++k, jj += seq[i].first)
                    dp[i + 1][jj] = 1;
        vector<vector<int> > ret;
        vector<int> path;
        function<void(int, int)> dfs = [&](int dep, int val) {
            if(val < 0 || !dp[dep][val])
                return;
            if(!dep) {
                ret.push_back(path);
                return;
            }
            --dep;
            int sz = path.size();
            for(int j = 0; j <= seq[dep].second && val >= 0; ++j, val -= seq[dep].first, path.push_back(seq[dep].first))
                dfs(dep, val);
            path.resize(sz);
        };
        dfs(n, target);
        return ret;
    }
};
