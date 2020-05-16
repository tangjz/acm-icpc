#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int n, rc, cc;
LL row[maxn], col[maxn];
struct Edge {
	LL u, v, w;
} e[maxn];
vector<LL> g[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
		row[rc++] = e[i].u;
		col[cc++] = e[i].v;
	}
	sort(row, row + rc);
	rc = unique(row, row + rc) - row;
	sort(col, col + cc);
	cc = unique(col, col + cc) - col;
	if((LL)rc * cc != n) {
		puts("0");
		return 0;
	}
	for(int i = 0; i < rc; ++i)
		for(int j = 0; j < cc; ++j)
			g[i].push_back(0LL);
	for(int i = 0; i < n; ++i) {
		e[i].u = lower_bound(row, row + rc, e[i].u) - row;
		e[i].v = lower_bound(col, col + cc, e[i].v) - col;
		g[e[i].u][e[i].v] += e[i].w;
	}
	for(int i = 1; i < rc; ++i)
		for(int j = 1; j < cc; ++j) {
			// g[0][j] * g[i][0] == g[0][0] * g[i][j]
			LL fz1 = g[0][0], fm1 = g[i][0], r1 = __gcd(fz1, fm1);
			fz1 /= r1;
			fm1 /= r1;
			LL fz2 = g[0][j], fm2 = g[i][j], r2 = __gcd(fz2, fm2);
			fz2 /= r2;
			fm2 /= r2;
			if(fz1 != fz2 || fm1 != fm2) {
				puts("0");
				return 0;
			}
		}
	LL low = 1, upp = g[0][0];
	for(int i = 1; i < cc; ++i)
		upp = __gcd(upp, g[0][i]);
	for(int i = 1; i < rc; ++i) {
		LL adt = g[0][0] / __gcd(g[0][0], g[i][0]);
		adt /= __gcd(low, adt);
		if(upp / low < adt || upp % (low * adt) != 0) {
			puts("0");
			return 0;
		}
		low *= adt;
	}
	int ans = 0;
	LL dif = upp / low;
	for(LL i = 1; i * i <= dif; ++i) {
		if(dif % i)
			continue;
		++ans;
		if(i * i < dif)
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}