#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 5001, maxm = 2001;
int n, m, cur, pre = 1;
LL f[2][maxn], c[maxn], s[maxn];
pair<int, int> a[maxn];
void solve(int L, int R, int pL, int pR) {
	if(L > R)
		return;
	int M = (L + R) >> 1, pM = pL;
	for(int i = pL; i < M && i <= pR; ++i) {
		LL tmp = f[pre][i] + s[M] - s[i] - a[i + 1].first * (c[M] - c[i]);
		if(f[cur][M] > tmp) {
			f[cur][M] = tmp;
			pM = i;
		}
	}
	solve(L, M - 1, pL, pM);
	solve(M + 1, R, pM, pR);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].second, &a[i].first);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) {
		c[i] = c[i - 1] + a[i].second;
		s[i] = s[i - 1] + (LL)a[i].first * a[i].second;
	}
	memset(f[cur] + 1, 0x3f, n * sizeof(LL));
	for(int i = 1; i <= m; ++i) {
		swap(cur, pre);
		memset(f[cur], 0x3f, (n + 1) * sizeof(LL));
		solve(0, n, 0, n);
	}
	printf("%lld\n", f[cur][n]);
	return 0;
}