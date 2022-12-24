#include <bits/stdc++.h>
const int maxn = (int)1e5 + 1, maxv = 13;
int t, n, tot, g[maxn][maxv], *f = g[0];
char buf[maxn], pat[maxv];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%s", &n, buf);
        char vL = '9', vR = '0';
        for(int i = 0; i < n; ++i) {
            vL = std::min(vL, buf[i]);
            vR = std::max(vR, buf[i]);
        }
        if(vL == vR) {
            printf("%d %d %d\n", n, 1, 1);
            continue;
        }
        int m = 0;
        char pL, pR;
        for(char low = vL; low < vR; ++low)
            for(char upp = low + 1; upp <= vR; ++upp) {
                tot = 0;
                for(char ch = vL; ch <= low; ++ch)
                    pat[tot++] = ch;
                for(char ch = upp; ch >= low; --ch)
                    pat[tot++] = ch;
                for(char ch = upp; ch <= vR; ++ch)
                    pat[tot++] = ch;
                memset(f, 0, tot * sizeof(int));
                for(int i = 0; i < n; ++i)
                    for(int j = 0; j < tot; ++j) {
                        f[j] += buf[i] == pat[j];
                        j && f[j] < f[j - 1] && (f[j] = f[j - 1]);
                    }
                if(m < f[tot - 1]) {
                    m = f[tot - 1];
                    pL = low;
                    pR = upp;
                }
            }
        tot = 0;
        for(char ch = vL; ch <= pL; ++ch)
            pat[tot++] = ch;
        for(char ch = pR; ch >= pL; --ch)
            pat[tot++] = ch;
        for(char ch = pR; ch <= vR; ++ch)
            pat[tot++] = ch;
        memset(g[0], 0, tot * sizeof(int));
        for(int i = 0; i < n; ++i) {
            int *pre = g[i], *cur = g[i + 1];
            for(int j = 0; j < tot; ++j) {
                cur[j] = pre[j] + (buf[i] == pat[j]);
                j && cur[j] < cur[j - 1] && (cur[j] = cur[j - 1]);
            }
        }
        int L = 0, R = 0;
        for(int i = n - 1, j = tot - 1; i >= 0; --i) {
            int *pre = g[i], *cur = g[i + 1];
            int lft = pre[j] + (buf[i] == pat[j]);
            int rht = j ? cur[j - 1] : -1;
            while(lft < rht) {
                if(pat[j - 1] == pL && pat[j] == pR) {
                    if(!R)
                        R = i;
                    else
                        L = i + 1;
                }
                --j;
                lft = pre[j] + (buf[i] == pat[j]);
                rht = j ? cur[j - 1] : -1;
            }
        }
        printf("%d %d %d\n", m, L + 1, R + 1);
    }
    return 0;
}