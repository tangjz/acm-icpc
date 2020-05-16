#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, maxm = maxn << 1 | 1;
int t, n, m;
LL a[maxn], b[maxm], pos;
bool check(LL dt) {
	// printf("dt %lld\n", dt);
	for(int i = 0; i < n; ++i) {
		b[i] = a[i] - dt;
		b[n + i] = a[i] + dt;
	}
	inplace_merge(b, b + n, b + n + n);
	for(int i = 0, j = 0, k = 0; i < n + n; ++i) {
		for( ; j < n && b[i] >= a[j] - dt; ++j);
		for( ; k < n && b[i] > a[k] + dt; ++k);
		if(j - k >= m + 1) {
			pos = b[i];
			return 1;
		}
	}
	return 0;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%lld", a + i);
		// sort(a, a + n);
		LL L = 0, R = (LL)2e9;
		while(L < R) {
			LL M = L + ((R - L) >> 1);
			if(check(M)) {
				R = M;
			} else {
				L = M + 1;
			}
		}
		check(L);
		printf("%lld\n", pos);
	}
	return 0;
}
