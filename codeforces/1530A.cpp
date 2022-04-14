#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
    static char buf[11];
    scanf("%s", buf);
    int ans = 0;
    for(int i = 0; buf[i]; ++i)
        ans = max(ans, (int)(buf[i] - '0'));
    printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}