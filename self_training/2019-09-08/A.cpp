#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e7 + 1, maxm = 100, maxv = (int)1.5e8, maxs = (int)2e4 + 1, maxc = (int)1e3 + 1;
int tot, pr[maxn >> 3 | 1], d[maxn], phi[maxn], f[maxm + 1];
void sieve(int L, int R) { // [L, R]
	if(L > R)
		return;
	if(R < maxn) {
		memcpy(f, phi + L, (R - L + 1) * sizeof(int));
		return;
	}
	assert(R - L + 1 <= maxm);
	static int g[maxm + 1];
	int *val = f - L, *rem = g - L, lim = (int)ceil(sqrtl(R));
	for(int i = L; i <= R; ++i) {
		val[i] = 1;
		rem[i] = i;
	}
	for(int i = 0, phi; pr[i] <= lim; ++i)
		for(int j = R / pr[i] * pr[i]; j >= L; j -= pr[i]) {
			for(phi = pr[i] - 1, rem[j] /= pr[i]; rem[j] % pr[i] == 0; rem[j] /= pr[i], phi *= pr[i]);
			val[j] *= phi;
		}
	for(int i = L; i <= R; ++i)
		if(rem[i] > 1)
			val[i] *= rem[i] - 1;
}
int cnt, pp[maxc], sz, que[maxs];
void dfs(int dep, int val, int phi) {
	if(phi & 1 || dep == cnt) {
		if(phi == 1)
			que[sz++] = val;
	} else {
		for(int i = dep; pp[i] - 1 <= phi; ++i) {
			if(phi % (pp[i] - 1) > 0)
				continue;
			int upp = (maxv + maxm - 1) / pp[i];
			if(val > upp)
				break;
			int nxt_val = val * pp[i], nxt_phi = phi / (pp[i] - 1);
			dfs(i + 1, nxt_val, nxt_phi);
			while(nxt_val <= upp && nxt_phi % pp[i] == 0)
				dfs(i + 1, nxt_val *= pp[i], nxt_phi /= pp[i]);
		}
	}
}
bool isPrime(int x) {
	if(x < maxn)
		return x == d[x];
	for(int i = 0; pr[i] * pr[i] <= x; ++i)
		if(x % pr[i] == 0)
			return 0;
	return 1;
}
void getCandidates(int n) {
	sz = 0;
	if(n & 1) {
		if(n == 1) {
			que[sz++] = 1;
			que[sz++] = 2;
		}
	} else {
		cnt = 0;
		for(int i = 0; (pr[i] - 1) * (pr[i] - 1) <= n; ++i)
			if(n % (pr[i] - 1) == 0)
				pp[cnt++] = pr[i];
		for(int i = 1; i * i <= n; ++i)
			if(n % i == 0 && isPrime(n / i + 1))
				pp[cnt++] = n / i + 1;
		assert(cnt < maxc);
		sort(pp, pp + cnt);
		cnt = unique(pp, pp + cnt) - pp;
		pp[cnt] = n + 2;
		dfs(0, 1, n);
	}
	assert(sz < maxs);
	sort(que, que + sz);
	sz = unique(que, que + sz) - que;
}
int seq[maxm + 1];
bool can[maxm + 1][maxm + 1];
int main() {
	d[1] = phi[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			phi[k] = phi[i] * pr[j];
			if(d[i] == pr[j])
				break;
			phi[k] -= phi[i];
		}
	}
	pr[tot] = maxn;
	int t;
	scanf("%d", &t);
	while(t--) {
		int pos = 0;
		for(int i = 0; i < maxm; ++i) {
			scanf("%d", seq + i);
			if(seq[i] < seq[pos])
				pos = i;
		}
		bool good = 1;
		for(int i = 0; pr[i] <= maxm; ++i) {
			for(int j = 0; j < pr[i]; ++j)
				can[i][j] = 1;
			for(int j = 0, k = 0; j < maxm; ++j, k = k ? k - 1 : pr[i] - 1)
				if(seq[j] % (pr[i] - 1) != 0)
					can[i][k] = 0;
			good = 0;
			for(int j = 0; j < pr[i]; ++j)
				good |= can[i][j];
			if(!good)
				break;
		}
		if(!good) {
			puts("NO");
			continue;
		}
		getCandidates(seq[pos]);
		bool chk = 0;
		for(int i = 0; i < sz; ++i) {
			int tmp = que[i] - pos;
			bool bad = tmp < 1 || tmp > maxv;
			for(int j = 0; !bad && pr[j] <= maxm; ++j)
				bad |= !can[j][tmp % pr[j]];
			if(bad)
				continue;
			sieve(tmp, tmp + maxm - 1);
			for(int j = 0; !bad && j < maxm; ++j)
				bad |= seq[j] != f[j];
			if(!bad) {
				chk = 1;
				puts("YES");
				printf("%d\n", tmp);
				break;
			}
		}
		if(!chk)
			puts("NO");
	}
	return 0;
}
