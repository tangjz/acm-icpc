#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e4 + 1;

int main() {
    int n, ans = 0;
    static int w[maxn], p[maxn], out[maxn];
    static int s[maxn], pL[maxn], pR[maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", w + i);
        s[i] = 0;
        pL[i] = pR[i] = i;
    }
    for(int i = 1; i <= n; ++i)
        scanf("%d", p + i);
    for(int i = n; i >= 1; --i) {
        out[i] = ans;
        int L = p[i], R = p[i];
        s[L] = w[L];
        if(L > 1 && s[L - 1]) {
            s[R] = s[L] + s[L - 1];
            L = pL[L - 1];
            s[L] = s[R];
            pL[R] = L;
            pR[L] = R;
        }
        if(R < n && s[R + 1]) {
            s[L] = s[R] + s[R + 1];
            R = pR[R + 1];
            s[R] = s[L];
            pL[R] = L;
            pR[L] = R;
        }
        ans = max(ans, s[L]);
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", out[i]);
    return 0;
}
