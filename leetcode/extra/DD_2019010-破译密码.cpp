#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 101, maxl = 201, maxv = (int)1e5 + 1, maxs = 7;

int main() {
    int n;
    static int sz[maxn], val[maxn][maxl];
    static char buf[maxn][maxl];
    static bool vis[maxv];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", buf[i]);
        sz[i] = strlen(buf[i]);
        memset(val[i], 0, sz[i] * sizeof(int));
    }
    for(int len = 1, pw = 10; ; ++len, pw *= 10) {
        memset(vis, 0, pw * sizeof(bool));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= sz[i] - len; ++j) {
                val[i][j] = val[i][j] * 10 + (buf[i][j + len - 1] - '0');
                vis[val[i][j]] = 1;
            }
        int pos = 0;
        for( ; pos < pw && vis[pos]; ++pos);
        if(pos < pw) {
            static char out[maxs];
            for(int i = 0; i < len; ++i, pos /= 10)
                out[len - 1 - i] = '0' + pos % 10;
            out[len] = '\0';
            puts(out);
            break;
        }
    }

    return 0;
}
