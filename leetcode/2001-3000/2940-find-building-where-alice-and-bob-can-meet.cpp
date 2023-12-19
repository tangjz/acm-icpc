class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& seq, vector<vector<int>>& que) {
        int n = seq.size(), m = que.size();
        vector<int> ans(m, -1);
        vector<vector<int> > eve(n);
        for(int i = 0; i < m; ++i) {
            int &u = que[i][0], &v = que[i][1];
            if(u > v)
                swap(u, v);
            if(u == v || seq[u] < seq[v]) {
                ans[i] = v;
                continue;
            }
            if(v + 1 < n)
                eve[v + 1].push_back(i);
        }
        vector<pair<int, int> > stk;
        for(int i = n - 1; i >= 0; --i) {
            pair<int, int> cur = {-seq[i], i};
            for( ; !stk.empty() && stk.back() > cur; stk.pop_back());
            stk.push_back(cur);
            for(int o: eve[i]) {
                cur = {-seq[que[o][0]], -1};
                auto it = lower_bound(stk.begin(), stk.end(), cur);
                if(it != stk.begin())
                    ans[o] = (--it) -> second;
            }
        }
        return ans;
    }
};
