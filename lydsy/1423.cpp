#include <bits/stdc++.h>
const int maxn = (int)1e3 + 1, maxv = (int)4e6 + 1, maxp = 283147;
int tot, pr[maxp];
void init() {
	static int d[maxv];
	tot = 0;
	memset(d, 0, sizeof d);
	for(int i = 2; i < maxv; ++i) {
		if(!d[i])
			pr[++tot] = d[i] = i;
		for(int j = 1, k; (k = i * pr[j]) < maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
}
int solve(int n) {
	static int his[maxn] = {};
	if(!his[n]) {
		static int sta, f[maxp], c[maxn];
		for(sta = 0; pr[sta] <= n; ++sta)
			f[sta] = sta;
		for(int i = sta, j = 0; i <= tot; ++i) {
			for( ; pr[j + 1] + n < pr[i]; ++j);
			if(j + 1 == i) {
				his[n] = pr[f[j]] + 1;
				break;
			}
			f[i] = f[j];
		}
		if(!his[n]) {
			int ans = 0;
			memset(c, 0, sta * sizeof(int));
			for(int i = sta; i <= tot; ++i)
				++c[f[i]];
			for(int i = 1; i < sta; ++i)
				if(c[ans] < c[i])
					ans = i;
			his[n] = pr[ans] + 1;
		}
	}
	return his[n] - 1;
}
int main() {
	int t, n;
	scanf("%d", &t);
	init();
	while(t--) {
		scanf("%d", &n);
		int ans = solve(n);
		if(!ans) {
			puts("B");
		} else {
			printf("A %d\n", ans);
		}
	}
	return 0;
}