#include <bits/stdc++.h>
using namespace std;
const int maxn = 500001, INF = (int)1e9 + 1;
int n, mod, f[maxn], tot, idx[maxn];
int main() {
	scanf("%d%d", &n, &mod);
	f[0] = 0;
	for(int i = 1; i < mod; ++i)
		f[i] = INF;
	for(int i = 1; i < n; ++i) {
		int adt;
		scanf("%d", &adt);
		for(int j = 0, jLim = __gcd(adt, mod); j < jLim; ++j) {
			int pos = tot = 0;
			idx[tot++] = j;
			for(int k = (j + adt) % mod; k != j; k = (k + adt) % mod) {
				if(f[k] < f[idx[pos]])
					pos = tot;
				idx[tot++] = k;
			}
			rotate(idx, idx + pos, idx + tot);
			for(int k = 1; k < tot; ++k)
				f[idx[k]] = min(f[idx[k]], f[idx[k - 1]] + adt);
		}
	}
	scanf("%d", &n);
	while(n--) {
		int x;
		scanf("%d", &x);
		puts(x >= f[x % mod] ? "TAK" : "NIE");
	}
	return 0;
}

