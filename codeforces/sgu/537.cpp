#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxc = 26, maxd = 10, maxl = 14;
const int maxe = 12, maxm = 17280, maxv = (int)1e7;

int ptot, pr[maxv >> 3 | 1];

void dfs(int rem, pair<LL, int> p[], int &cnt, LL out[], LL val) {
	if(!rem) {
		out[cnt++] = val;
		return;
	}
	pair<LL, int> &cur = p[--rem];
	dfs(rem, p, cnt, out, val);
	for(int i = 1; i <= cur.second; ++i)
		dfs(rem, p, cnt, out, val *= cur.first);
}

void solve() {
	static char buf[maxl + 1];
	scanf("%s", buf);
	int len = strlen(buf), m = 0;
	static LL coeff[maxc + 1];
	memset(coeff, 0, sizeof coeff);

	LL pw = 1;
	for(int i = len - 1; i >= 0; --i, pw *= 10) {
		int o = buf[i] - 'a';
		m += !coeff[o];
		coeff[o] += pw;
	}
	int fir = buf[0] - 'a';
	LL com = coeff[fir] * (maxd - 1);
	for(int i = 0, p = maxd - 2; i < maxc; ++i) {
		if(i == fir || !coeff[i])
			continue;
		com += coeff[i] * (p--);
	}
	// printf("m: %d, fir: %d (%lld), init: %lld\n", m, fir, coeff[fir], com);
	for(int i = 0; i < maxc; ++i) {
		if(i == fir || !coeff[i])
			continue;
		com = gcd(com, m == maxd ? abs(coeff[i] - coeff[fir]) : coeff[i]);
		// printf("add %d: %lld -> %lld\n", i, m == maxd ? abs(coeff[i] - coeff[fir]) : coeff[i], com);
	}
	if(m != maxd) {
		com = gcd(com, coeff[fir]);
		// printf("add %d: %lld -> %lld\n", fir, coeff[fir], com);
	}

	int pcnt = 0;
	static pair<LL, int> p[maxe + 1];
	for(int i = 0; (LL)pr[i] * pr[i] <= com; ++i) {
		if(com % pr[i] > 0)
			continue;
		for(p[pcnt] = {(LL)pr[i], 0}; com % pr[i] == 0; ++p[pcnt].second, com /= pr[i]);
		++pcnt;
		// printf("div (%lld, %d)\n", p[pcnt - 1].first, p[pcnt - 1].second);
	}
	if(com > 1) {
		p[pcnt++] = {com, 1};
		// printf("div (%lld, %d)\n", p[pcnt - 1].first, p[pcnt - 1].second);
	}

	int dcnt = 0;
	static LL fct[maxm + 1];
	dfs(pcnt, p, dcnt, fct, 1LL);
	sort(fct, fct + dcnt);
	for(int i = 0; i < dcnt; ++i)
		printf("%lld%c", fct[i], " \n"[i == dcnt - 1]);
}

int main() {
	static int d[maxv + 1] = {};
	for(int i = 2; i <= maxv; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}

	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("Case %d: ", Case);
		solve();
	}
	return 0;
}

/*

Inputcopy	Outputcopy
5
cat
bbb
ololo
lala
icpcicpc
Case 1: 1
Case 2: 1 3 37 111
Case 3: 1
Case 4: 1 101
Case 5: 1 73 137 10001
*/
