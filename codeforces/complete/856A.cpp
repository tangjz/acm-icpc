#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, maxm = (int)2e6 + 1;
int t, n, a[maxn], b[maxn], p[maxm];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		puts("YES");
		for(int i = 1, o = 0; i <= n; ++i) {
			for(++o; p[o] == Case; ++o);
			printf("%d%c", o, " \n"[i == n]);
			p[o] = Case;
			if(i < n)
				for(int j = 1; j <= n; ++j)
					for(int k = j + 1; k <= n; ++k)
						p[o - a[j] + a[k]] = Case;
		}
	}
	return 0;
}