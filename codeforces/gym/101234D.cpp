#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)1e5 + 1, maxLen = 18, maxm = 1 << maxLen | 1;
const int mod = (int)1e9 + 7;
const DB pi = acos((DB)-1); // double is enough
struct Complex {
    DB r, i;
    Complex() {}
    Complex(DB r, DB i) : r(r), i(i) {}
    Complex operator + (Complex const &t) const { return Complex(r + t.r, i + t.i); }
    Complex operator - (Complex const &t) const { return Complex(r - t.r, i - t.i); }
    Complex operator * (Complex const &t) const { return Complex(r * t.r - i * t.i, r * t.i + i * t.r); }
    Complex conj() const { return Complex(r, -i); }
} w[maxm << 1 | 1], f[2][maxm];
void initFFT(int len) {
	Complex *W = w + len;
    for(int i = 0; i < len; ++i) {
        int j = i, k = len >> 1; // 2 pi / len
        for( ; !(j & 1) && !(k & 1); j >>= 1, k >>= 1);
        W[i] = Complex(cos(pi / k * j), sin(pi / k * j));
    }
	for(int i = len - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void FFT(int n, Complex a[], int flag) {
	int i, j, k;
	for(i = 1, j = 0; i < n; ++i) {
		for(k = n >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			swap(a[i], a[j]);
	}
	Complex *W = w + 1, t;
	for(i = 1; i < n; i <<= 1)
		for(j = 0, W += i; j < n; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = W[k] * a[i + j + k];
				a[i + j + k] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
    if(flag != -1)
        return;
    reverse(a + 1, a + n);
    for(i = 0; i < n; ++i) {
		a[i].r /= n;
		a[i].i /= n;
	}
}
int tot, ord[maxn], fa[maxn];
vector<int> e[maxn];
bool ban[maxn];
void bfs_tree(int rt, int rfa = -1) {
	tot = 0;
	fa[rt] = rfa;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(int &v: e[u])
			if(v != fa[u] && !ban[v]) {
				fa[v] = u;
				ord[tot++] = v;
			}
	}
}
LL ans[maxn];
void dfs_tree(int rt) {
	bfs_tree(rt);
	int cnt = tot;
	static int sz[maxn];
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		sz[u] = 1;
		for(int &v: e[u])
			if(v != fa[u] && !ban[v]) {
				sz[u] += sz[v];
				mx = max(mx, sz[v]);
			}
		mx = max(mx, tot - sz[u]);
		if(mx < cnt) {
			rt = u;
			cnt = mx;
		}
	}
	cnt = tot;
	ban[rt] = 1;
	int PLEN, LEN;
	Complex *PF = f[0], *F = f[1];
	PLEN = 1;
	PF[0] = Complex(1, 0);
	for(int &tr: e[rt]) {
		if(ban[tr])
			continue;
		bfs_tree(tr, rt);
		LEN = 1;
		F[0] = Complex(1, 0);
		if(PLEN > 1) {
			PF[1].r += 1;
		} else {
			PF[PLEN++] = Complex(1, 0);
		}
		static int dis[maxn];
		dis[tr] = 0;
		for(int i = 1; i < tot; ++i) {
			int u = ord[i], p = fa[u];
			int DIS = dis[u] = dis[p] + 1;
			if(DIS < LEN) {
				F[DIS].r += 1;
			} else {
				F[LEN++] = Complex(1, 0);
			}
			++DIS;
			if(DIS < PLEN) {
				PF[DIS].r += 1;
			} else {
				PF[PLEN++] = Complex(1, 0);
			}
		}
		int CLEN = min(LEN + LEN - 1, cnt - 2), len;
		if(CLEN <= 0)
			continue;
		for(len = 1; len < LEN + LEN - 1; len <<= 1);
		for(int i = LEN; i < len; ++i)
			F[i] = Complex(0, 0);
		FFT(len, F, 1);
		for(int i = 0; i < len; ++i)
			F[i] = F[i] * F[i];
		FFT(len, F, -1);
		for(int i = 0, j = 2; i < CLEN; ++i, ++j)
			ans[j] -= (LL)(F[i].r + 0.5);
	}
	int CLEN = min(PLEN + PLEN - 1, cnt), len;
	for(len = 1; len < PLEN + PLEN - 1; len <<= 1);
	for(int i = PLEN; i < len; ++i)
		PF[i] = Complex(0, 0);
	FFT(len, PF, 1);
	for(int i = 0; i < len; ++i)
		PF[i] = PF[i] * PF[i];
	FFT(len, PF, -1);
	for(int i = 0; i < CLEN; ++i)
		ans[i] += (LL)(PF[i].r + 0.5);
	for(int &tr: e[rt])
		if(!ban[tr])
			dfs_tree(tr);
}
int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int len;
	for(len = 1; len < n + n; len <<= 1);
	initFFT(len);
	dfs_tree(1);
	int res = 0;
	for(int i = 0, prd = 1; i < n; ++i) {
		ans[i] = (ans[i] < mod ? ans[i] : ans[i] % mod) * prd % mod;
		prd = prd * (i + 1LL) % mod;
	}
	for(int i = n - 1, prd = 1; i >= 0; --i) {
		ans[i] = ans[i] * prd % mod;
		prd = prd * (i + 1LL) % mod;
	}
	for(int i = 0; i < n; ++i)
		(res += ans[i]) >= mod && (res -= mod);
	printf("%d\n", res);
	return 0;
}
