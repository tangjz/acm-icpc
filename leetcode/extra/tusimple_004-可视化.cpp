#include <bits/stdc++.h>
using namespace std;

const int maxn = 201;

int main() {
    int n, low = 0, upp = 0, cur = 0;
    static char buf[maxn], out[maxn][maxn];
    scanf("%d%s", &n, buf);
    for(int i = 0; i < n; ++i)
        if(buf[i] == '+') {
            upp = max(upp, ++cur);
        } else if(buf[i] == '-') {
            low = min(low, --cur);
        }
    for(int i = 0; i <= upp - low; ++i) {
        for(int j = 0; j < n; ++j)
            out[i][j] = '.';
        out[i][n] = '\0';
    }
    cur = 0;
    for(int i = 0; i < n; ++i)
        if(buf[i] == '+') {
            out[upp - cur][i] = '/';
            ++cur;
        } else if(buf[i] == '-') {
            --cur;
            out[upp - cur][i] = '\\';
        } else {
            out[upp - cur][i] = '-';
        }
    int L = 0, R = upp - low;
    while(L <= R) {
        bool empty = 1;
        for(int i = 0; empty && i < n; ++i)
            empty &= out[L][i] == '.';
        if(!empty)
            break;
        ++L;
    }
    while(L <= R) {
        bool empty = 1;
        for(int i = 0; empty && i < n; ++i)
            empty &= out[R][i] == '.';
        if(!empty)
            break;
        --R;
    }
    for(int i = L; i <= R; ++i)
        puts(out[i]);
    return 0;
}
