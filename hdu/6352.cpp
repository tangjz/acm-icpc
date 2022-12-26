#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxe = 7, maxs = (int)5e6 + maxn;
int pool[maxs], *tail = pool;
int pr[maxn][maxe], phi[maxn], *poly[maxn];
int t, n, m, ord[maxn];
int main() {
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        if(!pr[i][0])
            for(int j = i; j < maxn; j += i)
                pr[j][++pr[j][0]] = i;
        phi[i] = i;
        for(int j = 1; j <= pr[i][0]; ++j)
            phi[i] -= phi[i] / pr[i][j];
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        m = 0;
        for(int i = 1; i <= n; ++i) {
            if(n % i > 0)
                continue;
            ord[m++] = i;
            if(poly[i] != NULL)
                continue;
            int *seq = poly[i] = tail;
            tail += phi[i] + 1;
            memset(seq, 0, (phi[i] + 1) * sizeof(int));
            seq[0] = i > 1 ? 1 : -1;
            int pcnt = pr[i][0], *pp = pr[i] + 1;
            for(int j = 0; j < 1 << pcnt; ++j) {
                int val = i, sgn = 1;
                for(int k = 0; k < pcnt; ++k)
                    if((j >> k) & 1) {
                        val /= pp[k];
                        sgn = -sgn;
                    }
                if(sgn > 0)
                    for(int k = phi[i]; k >= val; --k)
                        seq[k] -= seq[k - val];
                else
                    for(int k = val; k <= phi[i]; ++k)
                        seq[k] += seq[k - val];
            }
        }
        sort(ord, ord + m, [&](int const &u, int const &v) {
            if(phi[u] != phi[v])
                return phi[u] < phi[v];
            for(int i = phi[u]; i >= 0; --i)
                if(poly[u][i] != poly[v][i])
                    return poly[u][i] < poly[v][i];
            return false;
        });
        static char buf[maxn << 3 | 1];
        char *ptr = buf;
        for(int i = 0; i < m; ++i) {
            int o = ord[i];
            *(ptr++) = '(';
            for(int j = phi[o], fir = 1; j >= 0; --j, fir = 0) {
                if(!poly[o][j])
                    continue;
                if(poly[o][j] < 0)
                    *(ptr++) = '-';
                else if(!fir)
                    *(ptr++) = '+';
                if(!j || abs(poly[o][j]) != 1)
                    ptr += sprintf(ptr, "%d", abs(poly[o][j]));
                if(j) {
                    *(ptr++) = 'x';
                    if(j > 1)
                        ptr += sprintf(ptr, "^%d", j);
                }
            }
            *(ptr++) = ')';
        }
        *ptr = '\0';
        assert(ptr - buf <= (maxn << 3));
        puts(buf);
    }
    return 0;
}
