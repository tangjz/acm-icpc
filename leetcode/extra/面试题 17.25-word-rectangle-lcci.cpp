class Solution {
public:
    vector<string> maxRectangle(vector<string>& words) {
        static const int maxl = 101, maxd = 26, maxs = (int)1e5 + 101;
        int mx = 0;
        for(auto &buf: words)
            mx = max(mx, (int)buf.size());
        vector<vector<string> > cand(mx + 1);
        static int tot, rt[maxl], nxt[maxs][maxd] = {};
        tot = 0;
        for(auto &buf: words) {
            int m = buf.size();
            if(cand[m].empty()) {
                rt[m] = ++tot;
                memset(nxt[tot], 0, sizeof(nxt[0]));
                // printf("rt %d: %d\n", m, rt[m]);
            }
            int cur = rt[m];
            for(char ch: buf) {
                int o = ch - 'a';
                if(!nxt[cur][o]) {
                    nxt[cur][o] = ++tot;
                    memset(nxt[tot], 0, sizeof(nxt[0]));
                    // printf("%d -> %d: %c\n", cur, nxt[cur][o], ch);
                }
                cur = nxt[cur][o];
            }
            cand[m].push_back(buf);
        }
        int ans = 0;
        vector<string> out;
        static int path[maxl], match[maxl][maxl];
        for(int i = mx; i > 0; --i) {
            if(cand[i].empty())
                continue;
            int sz = cand[i].size();
            for(int j = i; i * j > ans; --j) {
                if(cand[j].empty())
                    continue;
                function<bool(int)> dfs = [&](int dep) -> bool {
                    if(dep == j)
                        return 1;
                    for(int u = 0; u < sz; ++u) {
                        bool ban = 0;
                        for(int x = 0; x < i; ++x) {
                            int o = cand[i][u][x] - 'a';
                            match[dep + 1][x] = nxt[match[dep][x]][o];
                            if(!match[dep + 1][x]) {
                                ban = 1;
                                break;
                            }
                        }
                        path[dep] = u;
                        // printf("dfs %d (i %d j %d): check %s\n", dep, i, j, cand[i][u].c_str());
                        // for(int x = 0; x < i; ++x)
                        //     printf("%d -> %d: %c\n", match[dep][x], match[dep + 1][x], cand[i][u][x]);
                        if(!ban && dfs(dep + 1))
                            return 1;
                    }
                    return 0;
                };
                for(int x = 0; x < i; ++x)
                    match[0][x] = rt[j];
                if(dfs(0)) {
                    ans = i * j;
                    out.clear();
                    for(int x = 0; x < j; ++x)
                        out.push_back(cand[i][path[x]]);
                }
            }
        }
        return out;
    }
};
