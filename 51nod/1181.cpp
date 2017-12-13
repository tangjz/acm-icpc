#include <stdio.h>
const int maxn = (int)1e6 + 161;
int tot, pr[maxn], d[maxn];
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[++tot] = d[i] = i;
		for(int j = 1, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int n, m;
	scanf("%d", &n);
	for(m = 0; pr[m] <= tot && pr[pr[m]] < n; ++m);
	printf("%d\n", pr[pr[m]]);
	return 0;
}
