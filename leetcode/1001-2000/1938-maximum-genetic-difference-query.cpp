class Solution {
    int n, m, mx;
    vector<int> ans;
    vector<vector<int> > e;
    vector<vector<pair<int, int> > > que;
    struct Node {
        int cnt, nxt[2];
    };
    vector<Node> tr;
    void upd(int x, int v) {
        int rt = 0;
        for(int i = mx - 1; i >= 0; --i) {
            int o = (x >> i) & 1;
            if(!tr[rt].nxt[o]) {
                tr.push_back((Node){});
                tr[rt].nxt[o] = m++;
            }
            tr[rt].cnt += v;
            rt = tr[rt].nxt[o];
        }
        tr[rt].cnt += v;
    }
    int ask(int x) {
        int rt = 0;
        for(int i = mx - 1; i >= 0 && tr[rt].cnt > 0; --i) {
            int o = (x >> i) & 1;
            if(tr[rt].nxt[!o] && tr[tr[rt].nxt[!o]].cnt > 0) {
                x ^= (!o) << i;
                rt = tr[rt].nxt[!o];
            } else {
                x ^= (o) << i;
                rt = tr[rt].nxt[o];
            }
        }
        return x;
    }
    void dfs(int u) {
        upd(u, 1);
        for(auto &it: que[u]) {
            ans[it.first] = ask(it.second);
        }
        for(int v: e[u])
            dfs(v);
        upd(u, -1);
    }
public:
    vector<int> maxGeneticDifference(vector<int>& p, vector<vector<int>>& q) {
        n = (int)p.size();
        for(mx = 0; (1 << mx) <= n; ++mx);
        e.resize(n);
        que.resize(n);
        int rt = -1;
        for(int i = 0; i < n; ++i)
            if(p[i] != -1) {
                e[p[i]].push_back(i);
            } else {
                rt = i;
            }
        int k = q.size();
        ans.resize(k);
        for(int i = 0; i < k; ++i)
            que[q[i][0]].push_back({i, q[i][1]});
        tr.resize(m = 0);
        tr.push_back((Node){});
        ++m;
        dfs(rt);
        return ans;
    }
};
