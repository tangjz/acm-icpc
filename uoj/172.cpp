#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1;
int t, n, mod, nxt[maxn];
LL m, f[maxn], g[maxn];
char buf[maxn];
inline void upd(LL &x, LL y) {
	x > y && (x = y);
}
void append(int sta, int dif, int cnt) {
	static int idx[maxn << 1 | 1], que[maxn << 1 | 1];
	if(mod != sta) {
		memcpy(g, f, mod * sizeof(LL));
		memset(f, 0x3f, sta * sizeof(LL));
		for(int i = 0; i < mod; ++i)
			upd(f[g[i] % sta], g[i]);
		for(int i = 0, iLim = __gcd(sta, mod), adt = mod % sta; i < iLim; ++i) {
			int tot = 0, pos = 0;
			idx[tot++] = i;
			for(int j = i + adt < sta ? i + adt : i + adt - sta; j != i; (j += adt) >= sta && (j -= sta)) {
				idx[tot++] = j;
				if(f[idx[pos]] > f[j])
					pos = tot - 1;
			}
			rotate(idx, idx + pos, idx + tot);
			for(int j = 1; j < tot; ++j)
				upd(f[idx[j]], f[idx[j - 1]] + mod);
		}
		mod = sta;
	}
	if(cnt > 1)
		for(int i = 0, iLim = __gcd(dif, mod), adt = dif % mod; i < iLim; ++i) {
			int tot = 0, pos = 0;
			idx[tot++] = i;
			for(int j = i + adt < mod ? i + adt : i + adt - mod; j != i; (j += adt) >= mod && (j -= mod)) {
				idx[tot++] = j;
				if(f[idx[pos]] > f[j])
					pos = tot - 1;
			}
			rotate(idx, idx + pos, idx + tot);
			int L = 0, R = 0;
			for(int j = 0; j < tot; ++j) {
				for( ; L < R && j - que[L] >= cnt; ++L);
				for( ; L < R && f[idx[que[R - 1]]] + (LL)(j - que[R - 1]) * dif >= f[idx[j]]; --R);
				if(L < R)
					f[idx[j]] = min(f[idx[j]], f[idx[que[L]]] + sta + (LL)(j - que[L]) * dif);
				que[R++] = j;
			}
		}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%lld%s", &n, &m, buf);
		nxt[0] = nxt[1] = 0;
		for(int i = 1, j = 0; i < n; ++i) {
			for( ; j && buf[i] != buf[j]; j = nxt[j]);
			nxt[i + 1] = buf[i] == buf[j] ? ++j : 0;
		}
		memset(f, 0x3f, n * sizeof(LL));
		mod = f[0] = n;
		for(int i = nxt[n], j = i; i; i = j) {
			int cnt = 0, dif = i - nxt[i];
			for( ; j && j - nxt[j] == dif; j = nxt[j], ++cnt);
			if(j) {
				j = nxt[j];
				++cnt;
			}
			append(n - i, dif, cnt);
		}
		LL ans = 0;
		for(int i = 0; i < mod; ++i)
			if(f[i] <= m)
				ans += (m - f[i]) / mod + 1;
		printf("%lld\n", ans);
	}
	return 0;
}
