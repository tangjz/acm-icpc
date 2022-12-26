#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e4 + 1, maxd = 17, maxs = 1 << 16 | 1, INF = 0x3f3f3f3f;
int n, m;
vector<int> lft[maxd], rht[maxd];
LL w[maxd][maxd], f[maxs];
struct Gen {
	int val, prd, adt, mod;
	void read() {
		scanf("%d%d%d%d", &val, &prd, &adt, &mod);
	}
	int get() {
		int ret = val;
		val = ((LL)val * prd + adt) % mod;
		return ret;
	}
} genX, genY;
inline void upd(LL &x, LL y) {
	x > y && (x = y);
}
int main() {
	scanf("%d%d", &m, &n);
	genX.read();
	genY.read();
	for(int i = 0; i < n; ++i) {
		int x = genX.get(), y = genY.get();
		if(x & 1) {
			int v = (x + m + m - 1) / 2 % m;
			rht[v].push_back(y - x - m + 1);
		} else {
			int u = x / 2 % m;
			lft[u].push_back(x - y);
		}
	}
	for(int i = 0; i < m; ++i) {
		sort(lft[i].begin(), lft[i].end());
		sort(rht[i].begin(), rht[i].end());
	}
	for(int u = 0; u < m; ++u)
		for(int v = 0; v < m; ++v) {
			int len = 0;
			static int seq[maxn];
			for(vector<int>::iterator it = lft[u].begin(); it != lft[u].end(); ++it)
				seq[len++] = *it;
			for(vector<int>::iterator it = rht[v].begin(); it != rht[v].end(); ++it)
				seq[len++] = *it;
			inplace_merge(seq, seq + lft[u].size(), seq + len);
			LL sL = 0, sR = 0;
			for(int i = 0; i < len; ++i) {
				seq[i] += v - u;
				sR += seq[i];
			}
			int pos = seq[0] / m * m;
			if(pos > seq[0])
				pos -= m;
			w[u][v] = sR - (LL)len * pos;
			seq[len] = INF;
			for(int i = 1; i <= len; ++i) {
				sL += seq[i - 1];
				sR -= seq[i - 1];
				if(i < len - i) {
					pos = seq[i] / m * m;
					if(pos > seq[i])
						pos -= m;
					if(pos >= seq[i - 1])
						upd(w[u][v], sR - sL + (LL)(i + i - len) * pos);
				} else {
					pos = seq[i - 1] / m * m;
					if(pos < seq[i - 1])
						pos += m;
					if(pos <= seq[i])
						upd(w[u][v], sR - sL + (LL)(i + i - len) * pos);
				}
			}
		}
	for(int i = 0; i < (1 << m); ++i) {
		int cnt = 0;
		for(int j = 0; j < m; ++j)
			cnt += (i >> j) & 1;
		if(!cnt) {
			f[i] = 0;
			continue;
		}
		bool vis = 0;
		for(int j = 0; j < m; ++j) {
			if(!((i >> j) & 1))
				continue;
			LL tmp = f[i ^ (1 << j)] + w[cnt - 1][j];
			if(vis) {
				upd(f[i], tmp);
			} else {
				f[i] = tmp;
				vis = 1;
			}
		}
	}
	printf("%lld\n", f[(1 << m) - 1]);
	return 0;
}
