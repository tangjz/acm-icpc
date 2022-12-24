#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1, seed[2] = {29, 31}, mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
char buf[maxn];
int n, tot, pr[maxn >> 3 | 1], d[maxn];
pair<int, int> hh[maxn], pw[maxn];
inline pair<int, int> calc(int p, int l) { // hash[p-l+1..p]
	int fir = (hh[p].first - (LL)hh[p - l].first * pw[l].first) % mod[0];
	int sec = (hh[p].second - (LL)hh[p - l].second * pw[l].second) % mod[1];
	return make_pair(fir < 0 ? fir + mod[0] : fir, sec < 0 ? sec + mod[1] : sec);
}
int main() {
	scanf("%d%s", &n, buf);
	for(int i = 2; i <= n; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pw[0] = make_pair(1, 1);
	for(int i = 0; i < n; ++i) {
		int o = buf[i] - 'a' + 1;
		hh[i + 1] = make_pair((int)(((LL)hh[i].first * seed[0] + o) % mod[0]), (int)(((LL)hh[i].second * seed[1] + o) % mod[1]));
		pw[i + 1] = make_pair((int)((LL)pw[i].first * seed[0] % mod[0]), (int)((LL)pw[i].second * seed[1] % mod[1]));
	}
	scanf("%d", &n);
	while(n--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int len = r - l + 1, per = len;
		for(int tmp = per; tmp > 1; ) {
			int p = d[tmp], c = 0;
			for( ; d[tmp] == p; ++c, tmp /= p);
			for( ; c > 0 && calc(r, len - per / p) == calc(r - per / p, len - per / p); --c, per /= p);
		}
		printf("%d\n", per);
	}
	return 0;
}