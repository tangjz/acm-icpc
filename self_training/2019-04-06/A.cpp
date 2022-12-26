#include <bits/stdc++.h>
using namespace std;
const int maxn = 109;
int t, n, m;
char a[maxn], b[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%s", a);
		n = strlen(a);
		for(int i = 0; i < n; ++i) {
			b[i] = '0';
			if(a[i] == '4') {
				--a[i];
				++b[i];
			}
		}
		b[n] = '\0';
		for(m = 0; b[m] == '0'; ++m);
		printf("Case #%d: %s %s\n", Case, a, b + m);
	}
	return 0;
}