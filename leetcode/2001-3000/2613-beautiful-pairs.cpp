class Solution {
public:
    vector<int> beautifulPair(vector<int>& x, vector<int>& y) {
        typedef long long LL;
        int n = x.size();
        unordered_map<LL, int> ctr;
        vector<int> ord;
        for(int i = 0; i < n; ++i) {
            LL key = x[i] * (n + 1LL) + y[i];
            if((++ctr[key]) <= 2)
                ord.push_back(i);
        }
        auto cmp_x = [&](int const &u, int const &v) {
            return x[u] < x[v];
        };
        auto cmp_y = [&](int const &u, int const &v) {
            return y[u] < y[v];
        };
        sort(ord.begin(), ord.end(), cmp_x);
        pair<int, pair<int, int> > ans = {n + n + 1, {-1, -1}}, tmp;
        auto upd = [&](int u, int v) {
            if(u > v)
                swap(u, v);
            tmp = {abs(x[u] - x[v]) + abs(y[u] - y[v]), {u, v}};
            ans = min(ans, tmp);
        };
        function<void(int, int)> dfs = [&](int L, int R) {
            int len = R - L + 1;
            if(len <= 24) {
                for(int i = L; i < R; ++i)
                    for(int j = i + 1; j <= R; ++j)
                        upd(ord[i], ord[j]);
                sort(ord.begin() + L, ord.begin() + R + 1, cmp_y);
                return;
            }
            int M = L + len / 2, xM = x[ord[M]];
            dfs(L, M);
            dfs(M + 1, R);
            static vector<int> tmp, tmpL, tmpR;
            tmp.clear();
            tmpL.clear();
            tmpR.clear();
            auto chk = [&](int u, vector<int> &sp) {
                for(int i = sp.size() - 1; i >= 0; --i) {
                    int v = sp[i];
                    if(y[u] - y[v] > ans.first)
                        break;
                    upd(u, v);
                };
            };
            for(int i = L, j = M + 1; i <= M || j <= R; )
                if(j > R || (i <= M && y[ord[i]] <= y[ord[j]])) {
                    chk(ord[i], tmpR);
                    if(xM - x[ord[i]] <= ans.first)
                        tmpL.push_back(ord[i]);
                    tmp.push_back(ord[i++]);
                } else {
                    chk(ord[j], tmpL);
                    if(x[ord[j]] - xM <= ans.first)
                        tmpR.push_back(ord[j]);
                    tmp.push_back(ord[j++]);
                }
            for(int i = L; i <= R; ++i)
                ord[i] = tmp[i - L];
        };
        dfs(0, ord.size() - 1);
        return {ans.second.first, ans.second.second};
    }
};
