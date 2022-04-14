#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int main() {
    int n;
    scanf("%d", &n);
    int L = 1, R = n;
    vector<int> cache(n + 1);
    while(L < R) {
        int M = (L + R) >> 1, &p = cache[M], &q = cache[M + 1];
        if(!p) {
            printf("? %d\n", M);
            fflush(stdout);
            scanf("%d", &p);
        }
        if(!q) {
            printf("? %d\n", M + 1);
            fflush(stdout);
            scanf("%d", &q);
        }
        if(p < q) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    printf("! %d\n", L);
    fflush(stdout);
    return 0;
}