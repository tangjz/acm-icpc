#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 9, maxm = (int)1e5 + 1;
const LL lowx = 1, uppx = (LL)1e10, mod = 949848565645808449LL;
int t, n, L, R, tot, cnt[maxn], ord[2][maxn], cur, pre = 1;
LL inv[maxm], minv, maxv, dx, dy, dz, invdz, ans, val[maxn], tmp[maxn];
pair<LL, LL> que[maxn], seq[maxn];
inline int pos_inc(int x) {
    return (++x) < maxn ? x : x - maxn;
}
inline int pos_dec(int &x) {
    return (--x) < 0 ? x + maxn : x;
}
inline LL mod_mul(LL x, LL y) {
    return (__int128_t)x * y % mod;
}
inline LL mod_add(LL x, LL y) {
    return (x += y) < mod ? x : x - mod;
}
inline LL mod_sub(LL x, LL y) {
    return (x -= y) < 0 ? x + mod : x;
}
inline LL val_get(int pos) {
    LL ret = mod_add(mod_add(mod_mul(que[pos].first, dx), dy), mod_mul(que[pos].second, dz));
    return ret << 1 < mod ? ret : ret - mod;
}
inline void val_set(int pos, LL val) {
    que[pos].second = mod_mul(mod_sub(val, mod_add(mod_mul(que[pos].first, dx), dy)), invdz);
}
inline LL get_line_val(pair<LL, LL> pL, pair<LL, LL> pR, LL x) {
    LL slp = (pR.second - pL.second) / (pR.first - pL.first);
    return pL.second + (x - pL.first) * slp;
}
int main() {
    inv[1] = 1;
    for(int i = 2; i < maxm; ++i)
        inv[i] = mod - mod_mul(mod / i, inv[mod % i]);
    scanf("%d", &t);
    while(t--) {
        scanf("%d%I64d%I64d", &n, &minv, &maxv);
        L = 0, R = -1;
        dx = 1, dy = 0, dz = 1, invdz = 1;
        que[R = pos_inc(R)] = make_pair(lowx, 0);
        que[R = pos_inc(R)] = make_pair(uppx, 0);
        while(n--) {
            char op;
            LL val;
            scanf(" %c%I64d", &op, &val);
            if(op == '+') {
                dy = mod_add(dy, val);
            } else if(op == '-') {
                dy = mod_sub(dy, val);
            } else if(op == '*') {
                dx = mod_mul(dx, val);
                dy = mod_mul(dy, val);
                dz = mod_mul(dz, val);
                invdz = mod_mul(invdz, inv[val]);
            } else if(op == '@') {
                if(lowx < que[L].first) {
                    int lastP = L;
                    que[L = pos_dec(L)].first = lowx;
                    val_set(L, val_get(lastP));
                }
                if(uppx > que[R].first) {
                    int lastP = R;
                    que[R = pos_inc(R)].first = uppx;
                    val_set(R, val_get(lastP));
                }
                dx = mod_add(dx, val);
            }
            { // left -> right : shrink minv
                int lastP = -1;
                while(L != R && val_get(L) < minv) {
                    lastP = L;
                    L = pos_inc(L);
                }
                if(lastP != -1 && val_get(L) > minv) {
                    LL vL;
                    pair<LL, LL> qL = make_pair(que[lastP].first, val_get(lastP));
                    pair<LL, LL> qR = make_pair(que[L].first, vL = val_get(L));
                    LL slp = (qR.second - qL.second) / (qR.first - qL.first);
                    LL pL = (minv - qL.second - 1) / slp + qL.first + 1;
                    if(pL < que[L].first) {
                        vL = get_line_val(qL, qR, pL);
                        que[L = pos_dec(L)].first = pL;
                        val_set(L, vL);
                    }
                    if(pL > lowx && vL > minv) {
                        que[L = pos_dec(L)].first = pL - 1;
                        val_set(L, get_line_val(qL, qR, pL - 1));
                    }
                }
            }
            { // right -> left : shrink maxv
                int lastP = -1;
                while(L != R && val_get(R) > maxv) {
                    lastP = R;
                    R = pos_dec(R);
                }
                if(lastP != -1 && val_get(R) < maxv) {
                    LL vR;
                    pair<LL, LL> qL = make_pair(que[R].first, vR = val_get(R));
                    pair<LL, LL> qR = make_pair(que[lastP].first, val_get(lastP));
                    LL slp = (qR.second - qL.second) / (qR.first - qL.first);
                    LL pR = (maxv - qL.second) / slp + qL.first;
                    if(pR > que[R].first) {
                        vR = get_line_val(qL, qR, pR);
                        que[R = pos_inc(R)].first = pR;
                        val_set(R, vR);
                    }
                    if(pR < uppx && vR < maxv) {
                        que[R = pos_inc(R)].first = pR + 1;
                        val_set(R, get_line_val(qL, qR, pR + 1));
                    }
                }
            }
            if(val_get(L) < minv)
                val_set(L, minv);
            if(val_get(R) > maxv)
                val_set(R, maxv);
        }
        tot = 0;
        if(lowx < que[L].first)
            seq[tot++] = make_pair(lowx, val_get(L));
        for(int i = L, iLim = pos_inc(R); i != iLim; i = pos_inc(i))
            seq[tot++] = make_pair(que[i].first, val_get(i));
        if(que[R].first < uppx)
            seq[tot++] = make_pair(uppx, val_get(R));
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%I64d", val + i);
            ord[cur][i] = i;
        }
        if(n > 1) {
            memcpy(tmp, val, n * sizeof(LL));
            for(bool nxt = 1; nxt; ) {
                nxt = 0;
                pre ^= 1;
                cur ^= 1;
                memset(cnt, 0, n * sizeof(int));
                for(int i = 0; i < n; ++i)
                    ++cnt[tmp[i] % n];
                for(int i = 1; i < n; ++i)
                    cnt[i] += cnt[i - 1];
                for(int i = n - 1; i >= 0; --i) {
                    ord[cur][--cnt[tmp[ord[pre][i]] % n]] = ord[pre][i];
                    nxt |= tmp[ord[pre][i]] /= n;
                }
            }
        }
        ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            LL value = val[ord[cur][i]];
            for( ; seq[j].first < value; ++j);
            ans += seq[j].first == value ? seq[j].second : get_line_val(seq[j - 1], seq[j], value);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}