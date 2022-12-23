typedef long long LL;
const int maxn = (int)5e4 + 1, maxm = maxn * 94 + 1;
int ptot;
struct Node {
	int cnt, lch, rch;
} pool[maxm];

inline int newNode(int lch, int rch) {
	pool[ptot] = (Node){pool[lch].cnt + pool[rch].cnt, lch, rch};
	return ptot++;
}

class Solution {
public:
    long long maxXor(int n, vector<vector<int>>& edges, vector<int>& values) {
        vector<vector<int> > e(n);
        vector<int> par(n, -1), rt(n), ord(n);
        vector<LL> s(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        ord[0] = 0;
        for(int i = 0, sz = 1; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(v != par[u]) {
                    par[v] = u;
                    ord[sz++] = v;
                }
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], p = par[u];
            s[u] += values[u];
            if(p != -1)
                s[p] += s[u];
        }
        int mx = 0;
        for( ; (1LL << mx) <= s[0]; ++mx);
        LL ans = 0;
        ptot = 1;
        function<int(int, int, LL)> insertNode = [&](int dep, int x, LL v) {
            int rt = newNode(pool[x].lch, pool[x].rch);
            if(dep == -1) {
                pool[rt].cnt = pool[x].cnt + 1;
                return rt;
            }
            int o = (v >> dep) & 1, &ch = o ? pool[rt].rch : pool[rt].lch;
            ch = insertNode(dep - 1, ch, v);
            return rt;
        };
        function<void(int, int, int, LL)> checkNode = [&](int dep, int x, int p, LL v) {
            if(!x || !p)
                return;
            if(dep == -1) {
                ans = max(ans, v);
                return;
            }
            int o = (pool[x].lch && pool[p].rch) || (pool[x].rch && pool[p].lch);
            v |= (LL)o << dep;
            if(v + (1LL << dep) - 1 < ans)
                return;
            checkNode(dep - 1, pool[x].lch, o ? pool[p].rch : pool[p].lch, v);
            checkNode(dep - 1, pool[x].rch, o ? pool[p].lch : pool[p].rch, v);
        };
        function<int(int, int, int, int, LL)> mergeNode = [&](int dep, int x, int y, int p, LL v) {
            if(!x)
                return y;
            if(!y) {
                checkNode(dep, x, p, v);
                return x;
            }
            if(dep == -1) {
                checkNode(dep, x, p, v);
                int rt = newNode(0, 0);
                pool[rt].cnt = pool[x].cnt + pool[y].cnt;
                return rt;
            }
            int o = (pool[x].lch && pool[p].rch) || (pool[x].rch && pool[p].lch);
            v |= (LL)o << dep;
            return newNode(
                mergeNode(dep - 1, pool[x].lch, pool[y].lch, o ? pool[p].rch : pool[p].lch, v),
                mergeNode(dep - 1, pool[x].rch, pool[y].rch, o ? pool[p].lch : pool[p].rch, v)
            );
        };
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], p = par[u];
            rt[u] = insertNode(mx - 1, rt[u], s[u]);
            if(p != -1) {
                int x = rt[u], y = rt[p];
                if(pool[x].cnt > pool[y].cnt)
                    swap(x, y);
                rt[p] = mergeNode(mx - 1, x, y, y, 0LL);
            }
        }
        return ans;
    }
};
