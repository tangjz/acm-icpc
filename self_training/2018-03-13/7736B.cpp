#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, BASE = (int)1e9;
int n, m, a[maxn], b[maxn];
int main() {
	scanf("%d%d", &n, &m);
	int pos1 = 1, pos2 = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		if(a[pos1] < a[i])
			pos1 = pos2 = i;
		else if(a[pos1] == a[i])
			pos2 = i;
	}
	int pos3 = 1;
	for(int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
		if(b[pos3] < b[i])
			pos3 = i;
	}
	LL ans = 0;
	for(int i = 1; i <= pos1; ++i)
		ans += (LL)a[i] * BASE + b[1];
	for(int i = 2; i <= pos3; ++i)
		ans += (LL)a[pos1] * BASE + b[i];
	for(int i = pos1 + 1; i <= pos2; ++i)
		ans += (LL)a[i] * BASE + b[pos3];
	for(int i = pos3 + 1; i <= m; ++i)
		ans += (LL)a[pos2] * BASE + b[i];
	for(int i = pos2 + 1; i <= n; ++i)
		ans += (LL)a[i] * BASE + b[m];
	printf("%lld\n", ans);
	return 0;
}
