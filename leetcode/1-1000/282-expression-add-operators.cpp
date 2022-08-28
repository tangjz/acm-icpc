class Solution {
public:
    vector<string> addOperators(string num, int target) {
        typedef long long LL;
        int n = num.size();
        vector<vector<map<LL, vector<string> > > > prd(n, vector<map<LL, vector<string> > >(n));
        for(int len = 1; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                string buf = "";
                LL val = 0;
                for(int M = L; M < R; ++M) {
                    buf.push_back(num[M]);
                    val = val * 10 + (num[M] - '0');
                    if(buf[0] == '0' && L < M)
                        break;
                    buf.push_back('*');
                    for(auto &it: prd[M + 1][R]) {
                        LL nxt = val * it.first;
                        for(auto &rht: it.second)
                            prd[L][R][nxt].push_back(buf + rht);
                    }
                    buf.pop_back();
                }
                buf.push_back(num[R]);
                val = val * 10 + (num[R] - '0');
                if(buf[0] != '0' || len == 1)
                    prd[L][R][val].push_back(buf);
            }
        vector<string> ret;
        vector<map<LL, vector<string> > > pre(n);
        for(int i = 0; i + 1 < n; ++i) {
            pre[i] = prd[0][i];
            for(int j = 0; j < i; ++j)
                for(auto &it: pre[j])
                    for(auto &jt: prd[j + 1][i]) {
                        LL add = it.first + jt.first;
                        LL sub = it.first - jt.first;
                        for(auto &lft: it.second)
                            for(auto &rht: jt.second) {
                                pre[i][add].push_back(lft + "+" + rht);
                                pre[i][sub].push_back(lft + "-" + rht);
                            }
                    }
            for(auto &it: pre[i]) {
                auto add = prd[i + 1][n - 1].find(target - it.first);
                if(add != prd[i + 1][n - 1].end())
                    for(auto &lft: it.second)
                        for(auto &rht: add -> second)
                            ret.push_back(lft + "+" + rht);
                auto sub = prd[i + 1][n - 1].find(it.first - target);
                if(sub != prd[i + 1][n - 1].end())
                    for(auto &lft: it.second)
                        for(auto &rht: sub -> second)
                            ret.push_back(lft + "-" + rht);
            }
        }
        auto it = prd[0][n - 1].find(target);
        if(it != prd[0][n - 1].end())
            for(auto &mid: it -> second)
                ret.push_back(mid);
        return ret;
    }
};
