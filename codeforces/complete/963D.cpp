#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, seed = 27, mod1 = (int)1e9 + 7;
int n, q, len[maxn], rep[maxn], ord[maxn], ans[maxn];
char buf[maxn], pat[maxn];
LL pw[maxn], h[maxn], val[maxn];
unordered_map<LL, vector<int> > Hash;
int main() {
	scanf("%s%d", buf, &q);
	n = strlen(buf);
	pw[0] = 1;
	for(int i = 0; i < n; ++i) {
		int ch = buf[i] - 'a' + 1;
		LL h1 = h[i];
		h1 = (h1 * seed + ch) % mod1;
		h[i + 1] = h1;
		LL p1 = pw[i];
		p1 = p1 * seed % mod1;
		pw[i + 1] = p1;
	}
	for(int i = 0; i < q; ++i) {
		scanf("%d%s", rep + i, pat);
		len[i] = strlen(pat);
		LL h1 = 0;
		for(int j = 0; j < len[i]; ++j) {
			int ch = pat[j] - 'a' + 1;
			h1 = (h1 * seed + ch) % mod1;
		}
		val[i] = h1;
		ord[i] = i;
	}
	sort(ord, ord + q, [&](int const &u, int const &v) {
		return len[u] < len[v];
	});
	for(int o = 0, stp = 0; o < q; ++o) {
		int i = ord[o];
		int &res = ans[i] = maxn;
		if(stp != len[i]) {
			stp = len[i];
			unordered_map<LL, vector<int> >().swap(Hash);
			for(int p = o; p < q && len[ord[p]] == stp; ++p)
				Hash[val[ord[p]]] = vector<int>();
			LL p1 = mod1 - pw[stp];
			for(int j = 0, k = j + stp; k <= n; ++j, ++k) {
				LL h1 = h[j];
				LL h2 = h[k];
				h1 = (h1 * p1 + h2) % mod1;
				unordered_map<LL, vector<int> >::iterator it = Hash.find(h1);
				if(it != Hash.end())
					(it -> second).push_back(j);
			}
		}
		vector<int> const &seq = Hash[val[i]];
		int sz = seq.size();
		for(int j = 0, k = rep[i] - 1; k < sz; ++j, ++k)
			res = min(res, seq[k] - seq[j] + len[i]);
	}
	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i] < maxn ? ans[i] : -1);
	return 0;
}