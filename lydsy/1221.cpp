#include <cstdio>
#include <algorithm>
const int maxn = 1001, INF = 0x3f3f3f3f;
int n, cc, a[maxn], dsu[maxn], res[maxn];
std::pair<int, int> p[2];
int dsu_find(int x) {
	return x < 0 || dsu[x] < -1 ? x : (dsu[x] = dsu_find(dsu[x]));
}
int calc(int m) {
	int ret = m * cc;
	for(int i = 0; i < n; ++i) {
		int dt = std::min(m, a[i]), rem = a[i] - dt;
		m -= dt;
		while(rem) {
			int j = dsu_find(i - p[1].first);
			if(j < 0)
				break;
			int dt = std::min(rem, res[j]);
			ret += dt * p[1].second;
			rem -= dt;
			if(!(res[j] -= dt))
				dsu[j] = j - 1;
		}
		while(rem) {
			int j = dsu_find(i - p[0].first);
			if(j < 0)
				break;
			int dt = std::min(rem, res[j]);
			ret += dt * p[0].second;
			rem -= dt;
			if(!(res[j] -= dt))
				dsu[j] = j - 1;
		}
		if(rem)
			return INF;
		dsu[i] = -2;
		res[i] = a[i];
	}
	return ret;
}
int main() {
	int L = 0, R = 0;
	scanf("%d%d%d%d%d%d", &n, &p[0].first, &p[1].first, &cc, &p[0].second, &p[1].second);
	++p[0].first;
	++p[1].first;
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		L = std::max(L, a[i]);
		R += a[i];
	}
	if(p[0] > p[1])
		swap(p[0], p[1]);
	if(p[0].second < p[1].second)
		p[1] = p[0];
	while(R - L >= 4) {
		int ML = L + (R - L) / 3, MR = R - (R - L) / 3;
		if(calc(ML) < calc(MR))
			R = MR;
		else
			L = ML;
	}
	int ans = calc(L);
	for(++L; L <= R; ++L)
		ans = std::min(ans, calc(L));
	printf("%d\n", ans);
	return 0;
}