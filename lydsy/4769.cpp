#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 2000001;
int n, a[maxn], b[maxn];
long long ans;
void solve(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int cnt = 0, pL = L, pR = M + 1;
	while(pL <= M && pR <= R)
		if(a[pL] > a[pR]) {
			b[cnt++] = a[pR++];
		} else {
			ans += pR - M - 1;
			b[cnt++] = a[pL++];
		}
	ans += (M - pL + 1LL) * (R - M);
	while(pL <= M)
		b[cnt++] = a[pL++];
	while(pR <= M)
		b[cnt++] = a[pR++];
	memcpy(a + L, b, cnt * sizeof(int));
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	solve(0, n - 1);
	printf("%lld\n", ans);
	return 0;
}
