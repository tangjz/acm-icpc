class Solution {
    static const int maxv = 51;
    void dfs(int dep, int u, int p, vector<int> &nums, vector<vector<int> > &e, vector<pair<int, int> > &pos, vector<int> &ans) {
        int val = nums[u];
        pair<int, int> tmp = {-1, -1};
        for(int i = 1; i < maxv; ++i)
            if(pos[i] > tmp && gcd(val, i) == 1)
                tmp = pos[i];
        ans[u] = tmp.second;
        tmp = pos[val];
        pos[val] = {dep, u};
        for(int v : e[u]) {
            if(v == p)
                continue;
            dfs(dep + 1, v, u, nums, e, pos, ans);
        }
        pos[val] = tmp;
    }
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = (int)nums.size();
        vector<vector<int> > e(n, vector<int>());
        for(auto &it : edges) {
            int u = it[0], v = it[1];
            e[u].push_back(v);
            e[v].push_back(u);
        }
        vector<pair<int, int> > pos(maxv, {-1, -1});
        vector<int> ans(n, -1);
        dfs(0, 0, -1, nums, e, pos, ans);
        return ans;
    }
};
