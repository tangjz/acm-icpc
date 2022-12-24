#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int t, n, m, a[maxn], b[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < m; ++i)
			scanf("%d", b + i);
		sort(a, a + n, greater<int>());
		for( ; n && !a[n - 1]; --n);
		sort(b, b + m, greater<int>());
		for( ; m && !b[m - 1]; --m);
		if(n == m) {
			bool chk = 1;
			for(int i = 0; i < n; ++i)
				chk &= a[i] == b[i];
			puts(chk ? "Bob" : "Alice");
		} else {
			puts("Alice");
		}
	}
	return 0;
}