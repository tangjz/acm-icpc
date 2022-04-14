#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxv = 100;
void solve() {
    int n;
    static int seq[2][maxn];
    scanf("%d", &n);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < n; ++j) {
            scanf("%d", seq[i] + j);
        }
        sort(seq[i], seq[i] + n, greater<int>());
    }
    int L = 0, R = n << 2;
    while(L < R) {
        int M = (L + R) >> 1;
        int tot = n + M - ((n + M) >> 2);
        int rem = max(tot - M, 0);
        int lft = (tot - rem) * maxv, rht = 0;
        for(int i = 0; i < rem; ++i)
            lft += seq[0][i];
        for(int i = 0; i < tot && i < n; ++i)
            rht += seq[1][i];
        // printf("adt %d: %d %d\n", M, lft, rht);
        if(lft >= rht) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    printf("%d\n", L);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}