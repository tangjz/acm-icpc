#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxm = 169;
int n, tot, pr[maxn], d[maxn], dd[maxn], idx[maxn];
bitset<maxm> f[maxn], g[maxm], cur, res;
vector<int> pos;
bool vis[maxn];
int main() {
	scanf("%d", &n);
	d[1] = dd[1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(!d[i]) {
			idx[i] = tot;
			pr[tot++] = d[i] = i;
			dd[i] = (LL)i * i <= n ? 1 : i;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j) {
			d[k] = pr[j];
			dd[k] = dd[i];
			if(d[i] == pr[j])
				break;
		}
	}
	int sp = dd[n];
	res.reset();
	for(int tmp = n / sp; tmp > 1; ) {
		int pp = d[tmp], cc = 0;
		for( ; d[tmp] == pp; tmp /= pp, ++cc);
		if(cc & 1)
			res.set(idx[pp]);
	}
	if(sp == 1 && !res.any()) {
		printf("%d\n", n);
		return 0;
	}
	if(d[n] == n) {
		puts("-1");
		return 0;
	}
	for( ; --n; ) {
		int nn = dd[n];
		cur.reset();
		for(int tmp = n / nn; tmp > 1; ) {
			int pp = d[tmp], cc = 0;
			for( ; d[tmp] == pp; tmp /= pp, ++cc);
			if(cc & 1)
				cur.set(idx[pp]);
		}
		if(nn > 1 && vis[nn])
			cur ^= f[nn];
		for(int i : pos)
			if(cur.test(i))
				cur ^= g[i];
		if(nn > 1 && !vis[nn]) {
			vis[nn] = 1;
			f[nn] = cur;
			if(nn == sp) {
				res ^= cur;
				for(int i : pos)
					if(res.test(i))
						res ^= g[i];
			}
		} else {
			int i = cur._Find_first();
			if(i < (int)cur.size()) {
				pos.push_back(i);
				g[i] = cur;
				if(sp == 1 || vis[sp]) {
					if(res.test(i))
						res ^= cur;
				}
			}
		}
		if((sp == 1 || vis[sp]) && !res.any())
			break;
	}
	n -= !n;
	printf("%d\n", n);
	return 0;
}