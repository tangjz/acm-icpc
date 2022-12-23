class Solution {
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int ans = 0, n = nums.size();
        vector<vector<int> > e(n);
        vector<int> ord(n), par(n, -1), sub(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        ord[0] = 0;
        for(int i = 0, tot = 1; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u]) {
                if(v == par[u])
                    continue;
                par[v] = u;
                ord[tot++] = v;
            }
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i];
            sub[u] += nums[u];
            if(par[u] != -1)
                sub[par[u]] += sub[u];
        }
        int mx = sub[0];
        vector<int> ctr(mx + 1);
        for(int u: ord)
            ++ctr[sub[u]];
        for(int i = 1; i <= mx; ++i) {
            if(mx % i > 0)
                continue;
            int cnt = 0;
            for(int j = i; j <= mx; j += i)
                cnt += ctr[j];
            if(cnt == mx / i)
                ans = max(ans, cnt - 1);
        }
        return ans;
    }
};
