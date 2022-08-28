class Solution {
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int> > e(n);
        vector<int> seq = {0}, in(n), out(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        function<void(int, int)> dfs = [&](int u, int p) {
            in[u] = seq.size();
            seq.push_back(seq.back() ^ nums[u]);
            for(int v: e[u])
                if(v != p)
                    dfs(v, u);
            out[u] = seq.size() - 1;
        };
        seq.reserve(n);
        dfs(0, -1);
        int ans = INT_MAX;
        for(int i = 1; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                int uL = in[i], uR = out[i];
                int vL = in[j], vR = out[j];
                int u = seq[uR] ^ seq[uL - 1];
                int v = seq[vR] ^ seq[vL - 1];
                int w = seq.back();
                if(max(uL, vL) > min(uR, vR)) {
                    w ^= u ^ v;
                } else if(uR - uL > vR - vL) {
                    w ^= u;
                    u ^= v;
                } else {
                    w ^= v;
                    v ^= u;
                }
                int low = min(min(u, v), w), upp = max(max(u, v), w);
                ans = min(ans, upp - low);
            }
        return ans;
    }
};
