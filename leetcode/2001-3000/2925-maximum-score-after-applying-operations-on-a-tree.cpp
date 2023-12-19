class Solution {
    typedef long long LL;
    LL dfs(int u, int p, vector<vector<int> > &e, vector<int> &A) {
        LL ret = 0, tmp;
        bool leaf = 1;
        for(int v: e[u]) {
            if(v == p)
                continue;
            leaf = 0;
            ret += dfs(v, u, e, A);
        }
        ret = leaf ? A[u] : min(ret, (LL)A[u]);
        return ret;
    }
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& A) {
        int n = A.size();
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        LL sum = 0;
        for(int x: A)
            sum += x;
        LL res = dfs(0, -1, e, A);
        return sum - res;
    }
};
