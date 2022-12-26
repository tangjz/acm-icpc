#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxn2 = maxn << 1 | 1;
int t, n, seq[maxn2], sa[maxn], rk[maxn], ht[maxn], ctr[maxn], pos[maxn], *cur = ht;
bool typ[maxn2];
inline void pushS(int seq[], int x) {
    sa[cur[seq[x]]--] = x;
}
inline void pushL(int seq[], int x) {
    sa[cur[seq[x]]++] = x;
}
inline void inducedSort(int n, int m, int seq[], bool typ[], int n1, int v[]) {
    memset(sa, -1, n * sizeof(int));
    memset(ctr, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i)
        ++ctr[seq[i]];
    for(int i = 1; i < m; ++i)
        ctr[i] += ctr[i - 1];
    for(int i = 0; i < m; ++i)
        cur[i] = ctr[i] - 1;
    for(int i = n1 - 1; i >= 0; --i)
        pushS(seq, v[i]);
    for(int i = 1; i < m; ++i)
        cur[i] = ctr[i - 1];
    for(int i = 0; i < n; ++i)
        if(sa[i] > 0 && typ[sa[i] - 1])
            pushL(seq, sa[i] - 1);
    for(int i = 0; i < m; ++i)
        cur[i] = ctr[i] - 1;
    for(int i = n - 1; i >= 0; --i)
        if(sa[i] > 0 && !typ[sa[i] - 1])
            pushS(seq, sa[i] - 1);
}
inline void sais(int n, int m, int seq[], bool typ[], int pos[]) {
    int n1 = typ[n - 1] = 0, ch = rk[0] = -1, *seq1 = seq + n;
    for(int i = n - 2; i >= 0; --i)
        typ[i] = seq[i] == seq[i + 1] ? typ[i + 1] : (seq[i] > seq[i + 1]);
    for(int i = 1; i < n; ++i)
        rk[i] = typ[i - 1] && !typ[i] ? (pos[n1] = i, n1++) : -1;
    inducedSort(n, m, seq, typ, n1, pos);
    for(int i = 0, j, k, x, y; i < n; ++i) {
        if((x = rk[sa[i]]) < 0)
            continue;
        if(ch < 1 || pos[x + 1] - pos[x] != pos[y + 1] - pos[y])
            ++ch;
        else
            for(j = pos[x], k = pos[y]; j <= pos[x + 1]; ++j, ++k)
                if((seq[j] << 1 | typ[j]) != (seq[k] << 1 | typ[k])) {
                    ++ch;
                    break;
                }
        seq1[y = x] = ch;
    }
    if(ch + 1 < n1)
        sais(n1, ch + 1, seq1, typ + n, pos + n1);
    else
        for(int i = 0; i < n1; ++i)
            sa[seq1[i]] = i;
    for(int i = 0; i < n1; ++i)
        seq1[i] = pos[sa[i]];
    inducedSort(n, m, seq, typ, n1, seq1);
}
inline void SuffixArray() {
    int m = 101;
    memset(ctr, 0, m * sizeof(int));
    for(int i = 0; i <= n; ++i)
        ctr[seq[i]] = 1;
    for(int i = 1; i < m; ++i)
        ctr[i] += ctr[i - 1];
    for(int i = 0; i <= n; ++i)
        seq[i] = ctr[seq[i]] - 1;
    sais(n + 1, ctr[m - 1], seq, typ, pos);
    for(int i = 0; i < n; ++i)
        rk[sa[i] = sa[i + 1]] = i;
    for(int i = 0, j, k = ht[0] = 0; i < n; ++i) {
        if(k)
            --k;
        if(!rk[i])
            continue;
        for(j = sa[rk[i] - 1]; seq[i + k] == seq[j + k]; ++k);
        ht[rk[i]] = k;
    }
}
int vtot, etot, lnk[maxn2], fa[maxn2], sz[maxn2], dis[maxn2], ord[maxn2];
struct Edge {
    int nxt, v;
} e[maxn2];
inline int newNode() {
    lnk[vtot] = -1;
    fa[vtot] = sz[vtot] = dis[vtot] = 0;
    return vtot++;
}
inline void addEdge(int u, int v, int w) {
    fa[v] = u;
    dis[v] = dis[u] + w;
    e[etot] = (Edge){lnk[u], v};
    lnk[u] = etot++;
}
inline void SuffixTree() {
    vtot = etot = 0;
    int rt = newNode(), last;
    addEdge(rt, last = newNode(), n - sa[0]);
    ++sz[last];
    for(int i = 1; i < n; ++i) {
        int p = last;
        for( ; dis[p] > ht[i]; p = fa[p]);
        int dt = ht[i] - dis[p];
        if(dt > 0) {
            int q = newNode(), v = e[lnk[p]].v, w = dis[v] - dis[p];
            fa[q] = p;
            dis[q] = dis[p] + dt;
            e[lnk[p]].v = q;
            addEdge(q, v, w - dt);
            p = q;
        }
        addEdge(p, last = newNode(), n - sa[i] - ht[i]);
        ++sz[last];
    }
    vtot = 0;
    ord[vtot++] = rt;
    for(int i = 0; i < vtot; ++i)
        for(int u = ord[i], it = lnk[u]; it != -1; it = e[it].nxt)
            ord[vtot++] = e[it].v;
    for(int i = vtot - 1; i >= 0; --i)
        for(int u = ord[i], it = lnk[u]; it != -1; it = e[it].nxt)
            sz[u] += sz[e[it].v];
}
long long rem[maxn], que[maxn2];
inline long long HaffmanCode() {
    for(int i = 1; i < vtot; ++i)
        rem[sz[i]] += dis[i] - dis[fa[i]];
    int L = 0, R = 0;
    long long pre = 0, cur, ret = 0;
    for(int i = 1; i <= n; ++i) {
        if(!rem[i])
            continue;
        if(pre > 0) {
            cur = pre + i;
            ret += cur;
            pre = 0;
            --rem[i];
            if(cur <= n)
                ++rem[cur];
            else
                que[R++] = cur;
        }
        long long half = rem[i] >> 1;
        cur = i << 1;
        ret += cur * half;
        rem[i] -= half << 1;
        if(cur <= n)
            rem[cur] += half;
        else
            while(half--)
                que[R++] = cur;
        if(rem[i] > 0) {
            pre = i;
            --rem[i];
        }
    }
    if(pre > 0 && L < R) {
        cur = pre + que[L++];
        ret += cur;
        pre = 0;
        que[R++] = cur;
    }
    while(L + 1 < R) {
        pre = que[L++];
        cur = pre + que[L++];
        ret += cur;
        que[R++] = cur;
    }
    return ret;
}
inline bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}
int main() {
    scanf("%d", &t);
    while(t--) {
        static char buf[3 << 20 | 1];
        scanf("%d ", &n);
        fgets(buf, n * 3, stdin);
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; buf[j] && !isDigit(buf[j]); ++j);
            for(seq[i] = 0; isDigit(buf[j]); seq[i] = (seq[i] << 3) + (seq[i] << 1) + (buf[j++] - '0'));
            ++seq[i];
        }
        seq[n] = 0;
        SuffixArray();
        SuffixTree();
        long long fz = HaffmanCode(), fm = n * (n + 1LL) / 2, com = __gcd(fz, fm);
        if(fm == com)
            printf("%lld\n", fz / com);
        else
            printf("%lld/%lld\n", fz / com, fm / com);
    }
    return 0;
}
