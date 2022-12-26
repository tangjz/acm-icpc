#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int mod_sqrt(int x, int p) {
	if(!x || p <= 2)
		return x;
	auto mod_pow = [&p](int x, int k) { // 0 <= x < p, k >= 0
		int ret = 1;
		for( ; k > 0; k >>= 1, x = (LL)x * x % p)
			if(k & 1)
				ret = (LL)ret * x % p;
		return ret;
	};
	if(mod_pow(x, (p - 1) / 2) != 1)
		return -1;
	int w, y;
	do {
		w = rand() % (p - 1) + 1;
		y = ((LL)w * w + p - x) % p;
	} while(mod_pow(y, (p - 1) / 2) == 1);
	auto mod_mul = [&p, &y](pair<int, int> const &u, pair<int, int> const &v) {
		int fir = ((LL)u.first * v.first + (LL)u.second * v.second % p * y) % p;
		int sec = ((LL)u.first * v.second + (LL)u.second * v.first) % p;
		return make_pair(fir, sec);
	};
	pair<int, int> ret = make_pair(1, 0), tmp = make_pair(w, 1);
	for(int k = (p + 1) / 2; k > 0; k >>= 1, tmp = mod_mul(tmp, tmp))
		if(k & 1)
			ret = mod_mul(ret, tmp);
	return ret.first;
}
const int maxn = (int)1e4 + 1, maxc = 9, maxe = 27, maxs = 1 << 6 | 1, mod = (int)1e9 + 7;
int ptot, pr[maxn], d[maxn];
int t, n, m, s, cnt, lim[maxc], sz[maxc], ans;
pair<int, int> pp[maxc], tr[maxc][maxe], ways[maxc][maxs];
void pfs(int dep, int val, int upp) {
	if(dep == cnt) {
		int rem = upp / val, &csz = sz[cnt];
		pair<int, int> *vec = ways[cnt];
		for(int i = 0; i < csz; ++i) {
			int dx = val * vec[i].first + rem * vec[i].second;
			int dy = max(val * vec[i].second, rem * vec[i].first);
			int adt = 0;
			if(dx <= n && dy <= m)
				adt = (adt + (n - dx + 1LL) * (m - dy + 1)) % mod;
			if(dx <= m && dy <= n)
				adt = (adt + (m - dx + 1LL) * (n - dy + 1)) % mod;
			if(vec[i].second > 1)
				(adt += adt) >= mod && (adt -= mod);
			(ans += adt) >= mod && (ans -= mod);
		}
		return;
	}
	pfs(dep + 1, val, upp);
	for(int i = 1; i <= pp[dep].second; ++i)
		pfs(dep + 1, val *= pp[dep].first, upp);
}
void dfs(int dep, int val) {
	if(dep == cnt) {
		pfs(0, 1, s / val);
		return;
	}
	sz[dep + 1] = sz[dep];
	memcpy(ways[dep + 1], ways[dep], sz[dep] * sizeof(pair<int, int>));
	dfs(dep + 1, val);
	for(int i = 1; i <= lim[dep]; ++i) {
		int &csz = sz[dep], &nsz = sz[dep + 1] = 0;
		pair<int, int> *cur = ways[dep], *nxt = ways[dep + 1];
		auto append = [&nsz, &nxt](int u, int v) {
			if(u > v)
				swap(u, v);
			nxt[nsz++] = make_pair(u, v);
		};
		int a = tr[dep][i].first, b = tr[dep][i].second;
		for(int j = 0; j < csz; ++j) {
			int c = cur[j].first, d = cur[j].second;
			append(a * c + b * d, abs(a * d - b * c));
			append(a * d + b * c, abs(a * c - b * d));
		}
		sort(nxt, nxt + nsz);
		nsz = unique(nxt, nxt + nsz) - nxt;
		--pp[dep].second;
		dfs(dep + 1, val *= pp[dep].first);
	}
	pp[dep].second += lim[dep];
}
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[ptot] = maxn;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &s);
		int tmp = s;
		cnt = ans = 0;
		for(int i = 0; pr[i] * pr[i] <= tmp; ++i)
			if(tmp % pr[i] == 0) {
				int ex = 0;
				for(tmp /= pr[i], ++ex; tmp % pr[i] == 0; tmp /= pr[i], ++ex);
				pp[cnt++] = make_pair(pr[i], ex);
			}
		if(tmp > 1)
			pp[cnt++] = make_pair(tmp, 1);
		for(int i = 0; i < cnt; ++i)
			if(pp[i].first == 2) {
				lim[i] = 1;
				tr[i][1] = make_pair(1, 1);
			} else if((pp[i].first & 3) == 3) {
				lim[i] = 0;
			} else { // (pp[i].first & 3) == 1
				lim[i] = pp[i].second;
				int a = pp[i].first, b = mod_sqrt(pp[i].first - 1, pp[i].first);
				for( ; (LL)b * b > pp[i].first; swap(a, b), b %= a);
				int tmp = pp[i].first - b * b;
				a = (int)sqrt(tmp);
				for( ; a * a < tmp; ++a);
				for( ; a * a > tmp; --a);
				if(a > b)
					swap(a, b);
				tr[i][1] = make_pair(a, b);
				for(int j = 2; j <= lim[i]; ++j) {
					int c = tr[i][j - 1].first, d = tr[i][j - 1].second;
					int e = a * c + b * d, f = abs(a * d - b * c);
					if(__gcd(e, f) > 1) {
						e = a * d + b * c;
						f = abs(a * c - b * d);
					}
					if(e > f)
						swap(e, f);
					tr[i][j] = make_pair(e, f);
				}
			}
		sz[0] = 1;
		ways[0][0] = make_pair(0, 1);
		dfs(0, 1);
		(ans += ans) >= mod && (ans -= mod);
		printf("%d\n", ans);
	}
	return 0;
}
