#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxv = (int)5e8 + 1;
int n, m, a[maxn], b[maxn];
bool solve(int lim) {
	for(int i = 1, j = 1; i <= n; ++i) {
		int pL = min(a[i], b[j]);
		if(a[i] - pL > lim)
			continue;
		for( ; j <= m && b[j] < a[i]; ++j);
		for( ; j <= m; ++j) {
			int pR = b[j];
			if(pR - pL + min(a[i] - pL, pR - a[i]) > lim)
				break;
		}
		if(j > m)
			return 1;
	}
	return 0;
}
int solve() {
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	int L = 0, R = maxv << 1;
	while(L < R) {
		int M = (L + R) >> 1;
		if(solve(M)) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return L;
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int K, S, A, B, C, D;
		scanf("%d%d%d%d", &n, &m, &K, &S);
		assert(!S);
		for(int i = 1; i <= K; ++i)
			scanf("%d", a + i);
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= n; ++i)
			a[i] = ((LL)A * a[i - 2] + (LL)B * a[i - 1] + C) % D + 1;
		for(int i = 1; i <= K; ++i)
			scanf("%d", b + i);
		scanf("%d%d%d%d", &A, &B, &C, &D);
		for(int i = K + 1; i <= m; ++i)
			b[i] = ((LL)A * b[i - 2] + (LL)B * b[i - 1] + C) % D + 1;
		printf("Case #%d: %d\n", Case, solve());
	}
	return 0;
}