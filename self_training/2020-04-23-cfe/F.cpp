#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)5e5 + 3;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, a[maxn], p[maxn], m, b[maxn], pos[maxn];
LL bit[maxn], f[maxn], g[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", p + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", b + i);
		pos[b[i]] = i;
		g[i] = INF;
	}
	b[0] = 0;
	g[0] = INF;
	for(int i = 1; i <= n; ++i) {
		int j = pos[a[i]];
		f[i] = 0;
		if(j > 0) {
			int L = b[j - 1], R = b[j]; // (L, R]
			for(int x = L; x > 0; x -= x & -x)
				f[i] -= bit[x];
			for(int x = R; x > 0; x -= x & -x)
				f[i] += bit[x];
		}
		if(p[i] > 0)
			for(int x = a[i]; x <= n; x += x & -x)
				bit[x] += p[i];
	}
	g[m] = 0;
	LL adt = 0, neg = 0;
	for(int i = n; i >= 1; --i) {
		if(p[i] < 0)
			neg += p[i];
		else if(a[i] > b[m])
			adt += p[i];
		int j = pos[a[i]];
		if(!pos[a[i]])
			continue;
		if(p[i] < 0)
			f[i] -= p[i];
		g[j - 1] = min(g[j - 1], g[j] + f[i]);
	}
	if(g[0] < INF)
		printf("YES\n%lld\n", g[0] + adt + neg);
	else
		puts("NO");
	return 0;
}