#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxd = 26, mod = 1000000007;
int n, len[maxd | 1], seq[maxd | 1][maxn], ord[maxd | 1];
char buf[maxn];
bool ban[maxd | 1];
int main() {
    for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
        for(int i = 0; i < maxd; ++i) {
            len[i] = 0;
            ord[i] = i;
            ban[i] = 0;
        }
        while(n--) {
            scanf("%s", buf);
            int blen = strlen(buf);
            if(blen > 1)
                ban[(int)(buf[0] - 'a')] = 1;
            for(int i = 0, j; i < blen; ++i) {
                for(j = buf[blen - 1 - i] - 'a'; len[j] <= i; seq[j][len[j]++] = 0);
                ++seq[j][i];
            }
        }
        for(int i = 0; i < maxd; ++i)
            for(int j = 0; j < len[i]; ++j)
                if(seq[i][j] >= maxd) {
                    if(j + 1 == len[i])
                        seq[i][len[i]++] = 0;
                    seq[i][j + 1] += seq[i][j] / maxd;
                    seq[i][j] %= maxd;
                }
        std::sort(ord, ord + maxd, [&](int const &u, int const &v) {
            if(len[u] != len[v])
                return len[u] < len[v];
            for(int i = len[u] - 1, *su = seq[u], *sv = seq[v]; i >= 0; --i)
                if(su[i] != sv[i])
                    return su[i] < sv[i];
            return u < v;
        });
        int pos = 0, ans = 0;
        for( ; ban[ord[pos]]; ++pos);
        for(int i = 0, j = 0; i < maxd; ++i) {
            if(i == pos)
                continue;
            int o = ord[i], sum = 0;
            for(int k = len[o] - 1; k >= 0; --k)
                sum = (sum * 26LL + seq[o][k]) % mod;
            ans = (ans + (long long)sum * (++j)) % mod;
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
