#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1;
inline int getFloor(LL x, int y) { // y > 0
	int z = x / y;
	for( ; (LL)y * z <= x; ++z);
	for( ; (LL)y * z > x; --z);
	return z;
}
int t, n, p, q, a[maxn], ord[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &p, &q);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			ord[i] = i;
		}
		sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
			return a[u] < a[v];
		});
		int u = -1, v = -1, w = -1, mxFz = ~0u >> 1, mxFm = 1;
		for(int i = 1; i <= n; ++i) {
			int Az = a[ord[i]], L = i, R = i;
			for(int j = 1; j < i; ++j) {
				int Ay = a[ord[j]];
				for( ; L >= 1 && a[ord[L]] > Az - Ay; --L);
				for( ; R <= n && a[ord[R]] < Az + Ay; ++R);
				if(L + 1 > R - 1)
					continue;
				int Ax2upp = Ay * Ay + Az * Az + getFloor(-2LL * Ay * Az * p, q);
				int pL = L + 1, pR = R - 1;
				if(a[ord[pL]] * a[ord[pL]] > Ax2upp)
					continue;
				while(pL < pR) {
					int pM = (pL + pR + 1) >> 1, Ax = a[ord[pM]];
					if(Ax * Ax <= Ax2upp) {
						pL = pM;
					} else {
						pR = pM - 1;
					}
				}
				if(pL == i || pL == j)
					--pL;
				if(pL == i || pL == j)
					--pL;
				if(pL <= L)
					continue;
				int Ax = a[ord[pL]], fz = (Ay * Ay + Az * Az - Ax * Ax), fm = 2 * Ay * Az;
				if((LL)fz * mxFm < (LL)mxFz * fm) {
					u = ord[pL];
					v = ord[j];
					w = ord[i];
					mxFz = fz;
					mxFm = fm;
				}
			}
		}
		if(u == -1) {
			puts("-1");
		} else {
			printf("%d %d %d\n", u, v, w);
		}
	}
	return 0;
}