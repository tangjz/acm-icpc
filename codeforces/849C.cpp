#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 501;
int n, m, f[maxn];
int main() {
	scanf("%d", &n);
	for(m = 1; (f[m] = f[m - 1] + m - 1) <= n; ++m);
	char cur = 'a';
	if(!n)
		putchar('a');
	while(m-- > 2) {
		while(n >= f[m]) {
			for(int i = 0; i < m; ++i)
				putchar(cur);
			++cur;
			n -= f[m];
		}
	}
	putchar('\n');
	return 0;
}