class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        const static int maxn = 31, maxv = 501;
        static int st = 0, tim[maxn][maxv] = {};
        static vector<vector<int> > dp[maxn][maxv], NONE = {}, EMPTY = {{}};
        sort(candidates.begin(), candidates.end());
        ++st;
        function<vector<vector<int> >&(int, int)> dfs = [&](int dep, int sum) -> vector<vector<int> >& {
            if(sum < 0)
                return NONE;
            if(dep < 0)
                return sum > 0 ? NONE : EMPTY;
            if(tim[dep][sum] == st)
                return dp[dep][sum];
            tim[dep][sum] = st;
            auto &cur = dp[dep][sum];
            vector<vector<int> >().swap(cur);
            auto &skp = dfs(dep - 1, sum);
            cur.insert(cur.end(), skp.begin(), skp.end());
            int adt = candidates[dep];
            auto &nxt = dfs(dep, sum - adt);
            for(auto &it : nxt) {
                cur.push_back(it);
                cur.back().push_back(adt);
            }
            return cur;
        };
        return dfs((int)candidates.size() - 1, target);
    }
};
