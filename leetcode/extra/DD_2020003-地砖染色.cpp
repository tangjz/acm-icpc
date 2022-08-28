#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e4 + 1;

int main() {
    int n, m;
    static char buf[maxn];
    scanf("%d%d%s", &n, &m, buf);
    int ans = n;
    for(char ch = 'a'; ch <= 'z'; ++ch) {
        int cnt = 0;
        for(int i = 0; i < n; )
            if(buf[i] == ch) {
                ++i;
            } else {
                ++cnt;
                i += m;
            }
        ans = min(ans, cnt);
    }
    printf("%d\n", ans);
    return 0;
}
