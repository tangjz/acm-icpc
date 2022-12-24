#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef double DB;
typedef pair<int, int> Edge;
const int maxn = 32677, mod1 = 41, mod2 = 797, gen1 = 6, gen2 = 2, maxLen = 11, maxm = 1 << maxLen | 1;
const DB pi = acos(-1.0);
int t, n, f[maxn], val[mod1][mod2], per1[mod1], per2[mod2], ord1[mod1], ord2[mod2], c[mod1][mod2], d[mod1][mod2];
struct complex {
    DB r, i;
    complex() {}
    complex(DB r, DB i) : r(r), i(i) {}
    complex operator + (complex const &t) const {
        return complex(r + t.r, i + t.i);
    } complex operator - (complex const &t) const {
        return complex(r - t.r, i - t.i);
    } complex operator * (complex const &t) const {
        return complex(r * t.r - i * t.i, r * t.i + i * t.r);
    } complex conj() const {
        return complex(r, -i);
    }
} w[maxm], ff[mod1][maxm], gg[maxm];
void FFT(int n, complex a[], int flag) {
    static int bitLen = 0, bitRev[maxm] = {};
    if(n != (1 << bitLen)) {
        for(bitLen = 0; 1 << bitLen < n; ++bitLen);
        for(int i = 1; i < n; ++i)
            bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
    }
    for(int i = 0; i < n; ++i)
        if(i < bitRev[i]) std::swap(a[i], a[bitRev[i]]);
    for(int i = 1, d = 1; d < n; ++i, d <<= 1)
        for(int j = 0; j < n; j += d << 1)
            for(int k = 0; k < d; ++k) {
                complex &AL = a[j + k], &AH = a[j + k + d];
                complex TP = w[k << (maxLen - i)] * AH;
                AH = AL - TP, AL = AL + TP;
            }
    if(flag != -1)
        return;
    std::reverse(a + 1, a + n);
    for(int i = 0; i < n; ++i) a[i].r /= n;
}
void precalc() {
    for(int i = 0; i < maxn; ++i)
        c[ord1[i % mod1]][ord2[i % mod2]] = f[i];
    memset(d, 0, sizeof d);
    for(int i = 0; i < mod1; ++i) {
        for(int x = 0; x < 1 << maxLen; ++x)
            ff[i][x] = complex(x + 1 < mod2 ? c[i][x + 1] : 0, 0);
        FFT(1 << maxLen, ff[i], 1);
    }
    for(int i = 0; i < mod1; ++i) {
        for(int j = 0; j < mod1; ++j) {
            int k = i && j ? (i - 1 + j - 1) % (mod1 - 1) + 1 : 0;
            for(int x = 0; x < mod2; ++x) {
                d[k][0] += c[i][0] * c[j][x];
                if(x)
                    d[k][0] += c[i][x] * c[j][0];
            }
            for(int x = 0; x < 1 << maxLen; ++x)
                gg[x] = ff[i][x] * ff[j][x];
            FFT(1 << maxLen, gg, -1);
            for(int x = 0; x < 1 << maxLen; ++x)
                d[k][x % (mod2 - 1) + 1] += (int)(gg[x].r + 0.5);
        }
    }
    for(int i = 0; i < mod1; ++i)
        for(int j = 0; j < mod2; ++j)
            f[val[per1[i]][per2[j]]] = d[i][j];
}
int mu[maxn], deg[maxn], ord[maxn], dis[maxn], ans;
vector<Edge> e[maxn];
bool cmp(int const &x, int const &y) {
    return deg[x] > deg[y];
}
int main() {
    for(int i = 0, ilim = 1 << maxLen; i < ilim; ++i) {
        int j = i, k = ilim >> 1; // 2 pi / ilim
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        w[i] = complex(cos(pi / k * j), sin(pi / k * j));
    }
    for(int i = 0; i < maxn; ++i)
        val[i % mod1][i % mod2] = i;
    per1[1] = ord1[1] = 1;
    for(int i = 2; i < mod1; ++i) {
        per1[i] = per1[i - 1] * gen1 % mod1;
        ord1[per1[i]] = i;
    }
    per2[1] = ord2[1] = 1;
    for(int i = 2; i < mod2; ++i) {
        per2[i] = per2[i - 1] * gen2 % mod2;
        ord2[per2[i]] = i;
    }
    mu[1] = 1;
    for(int i = 1; i < maxn; ++i)
        for(int j = i + i; j < maxn; j += i)
            mu[j] -= mu[i];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(f, 0, sizeof f);
        while(n--) {
            int x;
            scanf("%d", &x);
            ++f[x];
        }
        precalc();
        ans = 3 * f[0] * f[1] * f[1];
        for(int i = 1; i < maxn; ++i)
            for(int j = i + i; j < maxn; j += i)
                f[i] += f[j];
        memset(deg, 0, sizeof deg);
        for(int i = 1; i < maxn; ++i) {
            vector<Edge>().swap(e[i]);
            ord[i] = i;
        }
        for(int i = 1; i < maxn; ++i) if(mu[i])
            for(int j = 1, x = i; x < maxn; ++j, x += i) if(mu[x])
                for(int k = j, y = x, lim = (maxn - 1) / j, z = x * k; y <= lim; ++k, y += i, z += x)
                    if(mu[y] && __gcd(j, k) == 1 && f[z]) {
                        ++deg[x];
                        e[x].push_back(make_pair(y, f[z]));
                        if(x < y) {
                            ++deg[y];
                            e[y].push_back(make_pair(x, f[z]));
                        }
                    }
        sort(ord + 1, ord + maxn, cmp);
        for(int i = 1; i < maxn; ++i) {
            int u = ord[i];
            if(!mu[u])
                continue;
            for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = it -> first, dv = it -> second;
                if(deg[u] < deg[v] || (deg[u] == deg[v] && u < v))
                    continue;
                dis[v] = dv;
            }
            int sgn = mu[u];
            for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = it -> first, dv = it -> second;
                if(deg[u] < deg[v] || (deg[u] == deg[v] && u < v))
                    continue;
                if(mu[v] < 0)
                    sgn = -sgn;
                for(vector<Edge>::iterator it = e[v].begin(); it != e[v].end(); ++it) {
                    int w = it -> first, dw = it -> second;
                    if(!dis[w] || deg[v] < deg[w] || (deg[v] == deg[w] && v < w))
                        continue;
                    if(mu[w] < 0)
                        sgn = -sgn;
                    int cnt = 3, way = sgn;
                    if(u != v)
                        way *= cnt--;
                    if(v != w)
                        way *= cnt--;
                    ans += way * dis[w] * dv * dw;
                    if(mu[w] < 0)
                        sgn = -sgn;
                }
                if(mu[v] < 0)
                    sgn = -sgn;
            }
            for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = it -> first;
                if(deg[u] < deg[v] || (deg[u] == deg[v] && u < v))
                    continue;
                dis[v] = 0;
            }
        }
        printf("%d\n", ans & ((1 << 30) - 1));
    }
    return 0;
}