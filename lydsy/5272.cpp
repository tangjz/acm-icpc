#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxm = 7;
int cnt, pr[maxm];
LL pool[maxn], *tail = pool, *low[maxm];
int main() {
	LL L, R;
	int mod = 1, tmp;
	scanf("%lld%lld%d", &L, &R, &tmp);
	for(int i = 2; i <= tmp; ++i) {
		if(i * i > tmp)
			i = tmp;
		if(tmp % i > 0)
			continue;
		int ex = 0;
		for(++ex, tmp /= i; tmp % i == 0; ++ex, tmp /= i);
		LL *seq = low[cnt] = tail;
		tail += i;
		memset(seq, -1, i * sizeof(LL));
		for(int j = 0; j < i; ++j) {
			int k = (LL)j * j % i;
			if(seq[k] == -1)
				seq[k] = j;
		}
		for(int j = 0; j < i; ++j) {
			if(seq[j] == -1) {
				seq[j] = R + 1;
				continue;
			}
			int dL = 1, dR = ex, u = seq[j], v = u ? i - u : 0;
			seq[j] *= seq[j];
			while(dL < dR) {
				int dM = (dL + dR) >> 1, ctr = 0;
				LL upp = seq[j] + dM * i;
				for(int k = 0, x = u, y = v; ctr < ex && (LL)x * x <= upp; ++k, x += i, y += i) {
					for(int rem = (upp - (LL)x * x) / i; rem > 0; ctr += rem, rem /= i);
					if(u != v && (LL)y * y <= upp)
						for(int rem = (upp - (LL)y * y) / i; rem > 0; ctr += rem, rem /= i);
				}
				if(ctr < ex) {
					dL = dM + 1;
				} else {
					dR = dM;
				}
			}
			seq[j] += dL * i;
		}
		mod *= (pr[cnt++] = i);
	}
	LL ans = 0;
	for(int i = 0; i < mod; ++i) {
		LL sta = 1;
		for(int j = 0; j < cnt; ++j)
			sta = max(sta, low[j][i % pr[j]]);
		LL adt = i - sta % mod;
		sta += adt < 0 ? adt + mod : adt;
		ans += (sta <= R ? (R - sta) / mod + 1 : 0) - (sta < L ? (L - 1 - sta) / mod + 1 : 0);
	}
	printf("%lld\n", ans);
	return 0;
}