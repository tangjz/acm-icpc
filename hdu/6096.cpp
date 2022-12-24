#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxm = 600001, maxd = 26, seed = 27, mod1 = 985661441, mod2 = 998244353;
const LL MSK = (1LL << 32) - 1;
int t, n, q, tot, rt[maxn], pw1[maxm], pw2[maxm];
char buf[maxm], *pos[maxn], *tail, pre[maxm], suf[maxm];
LL hh[maxn], preh[maxm], sufh[maxm];
struct Trie {
    int cnt, ch[maxd];
} e[maxm];
bool cmp(char *const &x, char *const &y) {
    return strcmp(x, y) < 0;
}
int length;
bool cmp2(char *const &x, char *const &y) {
    return strncmp(x, y, length) < 0;
}
void build(int &rt, char *ptr) {
    e[tot] = e[rt];
    rt = tot++;
    ++e[rt].cnt;
    if(*ptr)
        build(e[rt].ch[*ptr - 'a'], ptr - 1);
}
int main() {
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i < maxm; ++i) {
        pw1[i] = (LL)seed * pw1[i - 1] % mod1;
        pw2[i] = (LL)seed * pw2[i - 1] % mod2;
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &q);
        tail = buf;
        *tail++ = '\0';
        for(int i = 1; i <= n; ++i) {
            scanf("%s", tail);
            int h1 = 0, h2 = 0;
            for(pos[i] = tail; *tail; ++tail) {
                h1 = ((LL)h1 * seed + *tail - 'a' + 1) % mod1;
                h2 = ((LL)h2 * seed + *tail - 'a' + 1) % mod2;
            }
            hh[i] = (LL)h1 << 32 | h2;
            ++tail;
        }
        sort(pos + 1, pos + n + 1, cmp);
        sort(hh + 1, hh + n + 1);
        // if(unique(hh + 1, hh + n + 1) - hh - 1 < n)
        //     puts("error");
        // puts("sorted:");
        tot = 1;
        for(int i = 1; i <= n; ++i) {
            // puts(pos[i]);
            rt[i] = rt[i - 1];
            build(rt[i], pos[i] + strlen(pos[i]) - 1);
        }
        for(int i = 1; i <= q; ++i) {
            scanf("%s%s", pre + 1, suf + 1);
            int plen = strlen(pre + 1), slen = strlen(suf + 1), h1, h2;
            length = plen;
            int L = lower_bound(pos + 1, pos + n + 1, pre + 1, cmp2) - pos;
            int R = upper_bound(pos + 1, pos + n + 1, pre + 1, cmp2) - pos;
            // printf("query [%d, %d]\n", L, R - 1);
            if(L >= R) {
                puts("0");
                continue;
            }
            h1 = h2 = 0;
            for(int i = 1; i <= plen; ++i) {
                h1 = ((LL)h1 * seed + pre[i] - 'a' + 1) % mod1;
                h2 = ((LL)h2 * seed + pre[i] - 'a' + 1) % mod2;
                preh[i] = (LL)h1 << 32 | h2;
            }
            h1 = h2 = 0;
            for(int i = 1; i <= slen; ++i) {
                h1 = ((LL)h1 * seed + suf[i] - 'a' + 1) % mod1;
                h2 = ((LL)h2 * seed + suf[i] - 'a' + 1) % mod2;
                sufh[i] = (LL)h1 << 32 | h2;
            }
            int rL = rt[L - 1], rR = rt[R - 1];
            for(char *ptr = suf + slen; *ptr; --ptr) {
                rL = e[rL].ch[*ptr - 'a'];
                rR = e[rR].ch[*ptr - 'a'];
            }
            int ret = e[rR].cnt - e[rL].cnt;
            if(!ret) {
                puts("0");
                continue;
            }
            for(int i = 1; i <= plen && i <= slen; ++i) {
                LL preL = preh[plen - i], preR = preh[plen];
                int h1 = ((preR >> 32) - (LL)pw1[i] * (preL >> 32)) % mod1;
                h1 < 0 && (h1 += mod1);
                int h2 = ((preR & MSK) - (LL)pw2[i] * (preL & MSK)) % mod2;
                h2 < 0 && (h2 += mod2);
                if(((LL)h1 << 32 | h2) == sufh[i]) {
                    h1 = ((LL)pw1[slen] * (preL >> 32) + (sufh[slen] >> 32)) % mod1;
                    h2 = ((LL)pw2[slen] * (preL & MSK) + (sufh[slen] & MSK)) % mod2;
                    int idx = lower_bound(hh + 1, hh + n + 1, (LL)h1 << 32 | h2) - hh;
                    if(hh[idx] == ((LL)h1 << 32 | h2))
                        --ret;
                }
            }
            printf("%d\n", ret);
        }
    }
    return 0;
}