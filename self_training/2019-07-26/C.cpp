#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxd = 20, maxv = (int)1e7 + 1;
int tot, pr[maxv >> 3 | 1], d[maxv];
int n, a[maxn], b[maxn], Log[maxn], st[maxd][maxn];
struct Record {
	int las, val, pre;
} his[maxv];
int main() {
	for(int i = 2; i < maxv; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &n);
	Log[0] = -1;
	int *f = st[0];
	for(int i = 1; i <= n; ++i) {
		Log[i] = Log[i >> 1] + 1;
		scanf("%d%d", a + i, b + i);
		for(int tmp = b[i]; tmp > 1; ) {
			int pp = d[tmp], cc = 0;
			for( ; d[tmp] == pp; tmp /= pp, ++cc);
			for(int j = 0, pw = 1; j < cc; ++j) {
				pw *= pp;
				Record &cur = his[pw];
				int tp = a[i] % pw;
				if(!cur.pre || cur.val != tp) {
					cur.las = cur.pre;
					cur.val = tp;
				}
				f[i] = max(f[i], cur.las + 1);
				cur.pre = i;
			}
		}
	}
	for(int i = 1; i <= Log[n]; ++i)
		for(int j = 1; j + (1 << i) - 1 <= n; ++j)
			st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	scanf("%d", &n);
	while(n--) {
		int L, R;
		scanf("%d%d", &L, &R);
		int d = Log[R - L + 1];
		int val = max(st[d][L], st[d][R - (1 << d) + 1]);
		puts(val <= L ? "Yes" : "No");
	}
	return 0;
}
