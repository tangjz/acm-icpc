#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e3 + 1, mod = (int)1e9 + 7;
int t, n, a, b;
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &a, &b);
		for(int i = 0; i < n; ++i)
			buf[i] = i < a ? (i < b ? 'a' + i : 'a') : buf[i - a];
		buf[n] = '\0';
		puts(buf);
	}
	return 0;
}