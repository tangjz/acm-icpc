#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int main() {
    int n;
    static char buf[maxn];
    scanf("%d%s", &n, buf);
    int L = 0, R = n - 1;
    for(bool ok = 0; L < n && (buf[L] != 'T' || !ok); ok |= buf[L++] == 'M');
    for(bool ok = 0; L < R && (buf[R] != 'M' || !ok); ok |= buf[R--] == 'T');
    if(L + 1 < R) {
        buf[R] = '\0';
        puts(buf + L + 1);
    }
    return 0;
}
