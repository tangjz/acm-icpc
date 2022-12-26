#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxp = 101;
int t, tot, pr[maxp], d[maxp];
LL lim;
int dfs(int dep, int upp, LL val, int sig) {
	int ret = sig;
	LL plim = lim / pr[dep];
	for(int i = 1; i <= upp && val <= plim; ++i)
		ret = max(ret, dfs(dep + 1, i, val *= pr[dep], sig * (i + 1)));
	return ret;
}
int main() {
	for(int i = 2; i < maxp; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &lim);
		printf("%d\n", dfs(0, maxp, 1, 1));
	}
	return 0;
}
