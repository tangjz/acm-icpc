#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)4e5 + 1, maxd = 19, maxm = (int)2e7 + 1;
const LL INF = (LL)2e18;
int n, m = 1, mx, fa[maxd][maxn];
LL s[maxd][maxn];
int main() {
	scanf("%d", &n);
	for(mx = 0; 1 << mx <= n; ++mx)
		s[mx][0] = s[mx][1] = INF;
	s[0][1] = 0;
	for(int i = 1; i <= n; ++i) {
		static int las = 0;
		int typ;
		LL p, q;
		scanf("%d%lld%lld", &typ, &p, &q);
		p ^= las;
		q ^= las;
		//printf("real: %d %lld %lld\n", typ, p, q);
		if(typ == 1) {
			for(int i = mx - 1; i >= 0; --i)
				if(s[0][fa[i][p]] < q)
					p = fa[i][p];
			if(s[0][p] < q)
				p = fa[0][p];
			fa[0][++m] = p;
			s[0][m] = q;
			//printf("add %d to %d\n", m, fa[0][m]);
			for(int i = 1; i < mx; ++i) {
				fa[i][m] = fa[i - 1][fa[i - 1][m]];
				s[i][m] = min(s[i - 1][m] + s[i - 1][fa[i - 1][m]], INF);
				//printf("%d: %d %lld\n", i, fa[i][m], s[i][m]);
			}
		} else {
			int ans = 0;
			for(int i = mx - 1; i >= 0; --i)
				if(s[i][p] <= q) {
					q -= s[i][p];
					p = fa[i][p];
					ans |= 1 << i;
				}
			printf("%d\n", las = ans);
		}
	}
	return 0;
}
