#include <bits/stdc++.h>
using namespace std;

const int maxn = 101;

int main() {
    int ans = 0;
    static char buf[maxn];
    scanf("%s", buf);
    for(int i = 0; buf[i]; ) {
        if(buf[i] < '0' || buf[i] > '9') {
            ++i;
            continue;
        }
        ++ans;
        for( ; buf[i] && buf[i] >= '0' && buf[i] <= '9'; ++i);
    }
    printf("%d\n", ans);
    return 0;
}
