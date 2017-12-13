#include <stdio.h>
const int maxn = 31623;
int tot, pr[maxn], d[maxn];
bool isprime(int x) {
	if(x < maxn)
		return d[x] == x;
	for(int i = 0; pr[i] * pr[i] <= x; ++i)
		if(x % pr[i] == 0)
			return 0;
	return 1;
}
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxn;
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		puts(isprime(n) ? "Yes" : "No");
	}
	return 0;
}
