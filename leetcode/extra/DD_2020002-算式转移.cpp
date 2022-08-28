#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int main() {
    int n;
    static int val[maxn];
    static char op[maxn], buf[3];
    scanf("%d%d", &n, val + 0);
    for(int i = 1; i < n; ++i) {
        scanf("%s%d", buf, val + i);
        op[i] = buf[0];
    }
    op[0] = op[n] = '\0';
    for(int i = 0, j; i + 1 < n; i = j) {
        for(j = i + 1; j + 1 < n && op[j + 1] == op[i + 1]; ++j);
        int L = i, R = j;
        if(op[i + 1] == '+' || op[i + 1] == '-') {
            L += i > 0 || op[i + 1] != '+';
            R -= R + 1 < n && (op[R + 1] == '*' || op[R + 1] == '/');
        } else if(op[i + 1] == '*') {
            L += i > 0 && op[i] == '/';
        } else {
            ++L;
        }
        sort(val + L, val + R + 1);
    }
    printf("%d", val[0]);
    for(int i = 1; i < n; ++i)
        printf(" %c %d", op[i], val[i]);
    puts("");
    return 0;
}
