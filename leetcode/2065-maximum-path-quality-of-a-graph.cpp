class Solution {
    void dfs(int tim, int pos, int sum, vector<int> &ctr, vector<int>& val, vector<vector<pair<int, int> > >& e, int maxTime, int &ans) {
        if(!pos && sum > ans) {
            // printf("%d %d:", tim, sum);
            // for(int i = 0; i < (int)ctr.size(); ++i)
            //     if(ctr[i] > 0)
            //         printf(" %d (%d)", i, ctr[i]);
            // puts("");
            ans = sum;
        }
        if(tim + 10 > maxTime)
            return;
        for(auto &it: e[pos]) {
            int nxt = it.first;
            int nxtTim = tim + it.second;
            if(nxtTim > maxTime)
                continue;
            int nxtSum = sum;
            if(!ctr[nxt]) {
                nxtSum += val[nxt];
            }
            ++ctr[nxt];
            // printf("in %d\n", nxt);
            dfs(nxtTim, nxt, nxtSum, ctr, val, e, maxTime, ans);
            // printf("out %d\n", nxt);
            --ctr[nxt];
        }
    }
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size(), ans = 0;
        vector<vector<pair<int, int> > > e(n);
        for(auto &it: edges) {
            int u = it[0], v = it[1], w = it[2];
            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }
        vector<int> ctr(n);
        ++ctr[0];
        dfs(0, 0, values.front(), ctr, values, e, maxTime, ans);
        return ans;
    }
};
