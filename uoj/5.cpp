#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
int t, len, fail[maxn], half[maxn], dep[maxn];
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		len = strlen(buf);
		int ans = 1;
		dep[1] = 1;
		for(int i = 1, j; i < len; ++i) {
			for(j = fail[i]; j && buf[i] != buf[j]; j = fail[j]);
			fail[i + 1] = buf[i] == buf[j] ? j + 1 : 0;
			dep[i + 1] = dep[fail[i + 1]] + 1;
			for(j = half[i]; j && buf[i] != buf[j]; j = fail[j]);
			for(j = buf[i] == buf[j] ? j + 1 : 0; j > (i + 1) / 2; j = fail[j]);
			half[i + 1] = j;
			ans = ans * (dep[half[i + 1]] + 1LL) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
