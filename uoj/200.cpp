#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)1.5e5 + 1, maxq = maxn;
const int maxp = ~0U >> 1, maxew = (int)5e4 + 1, maxqw = (int)1e9 + 1;
int n, m, q, mod, ans[maxq];
struct Edge {
	int u, v, w;
} e[maxm], que[maxq];
inline int mod_add(int x, int y) {
	return (x += y - mod) < 0 ? x + mod : x;
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
inline void mod_inc(int &x, int y) {
	(x += y - mod) < 0 && (x += mod);
}
inline void mod_inc_mul(int &x, int y, int z) {
	y && z && (x = (x + (LL)y * z) % mod);
}
inline int mod_inv(int x) {
	int y = mod, u = 1, v = 0;
	while(x) {
		int q = y / x;
		tie(x, y) = make_pair(y - q * x, x);
		tie(u, v) = make_pair(v - q * u, u);
	}
	assert(y == 1);
	return v < 0 ? v + mod : v;
}
inline int mod_pow(int x, int k) {
	int ret = mod > 1 ? 1 : 0;
	for( ; k > 0; x = (LL)x * x % mod, k >>= 1)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
vector<int> factorize(int x) {
	vector<int> pr;
	for(int i = 2; i <= x; ++i) {
		if(i * i > x)
			i = x;
		if(x % i == 0) {
			for(x /= i; x % i == 0; x /= i);
			pr.push_back(i);
		}
	}
	return pr;
}
const int maxLen = 16, maxN = 1 << maxLen | 1;
int w[maxN << 1 | 1];
void NTT_init(const int maxLen = ::maxLen) {
	assert((int)factorize(mod).size() == 1 && !((mod - 1) & ((1 << maxLen) - 1)));
	vector<int> pr = factorize(mod - 1);
	int gen;
	for(gen = 2; ; ++gen) {
		bool chk = 1;
		for(int p : pr)
			chk &= mod_pow(gen, (mod - 1) / p) != 1;
		if(chk)
			break;
	}
	assert(gen == 3);
	int *W = w + (1 << maxLen);
	W[0] = 1;
	W[1] = mod_pow(gen, (mod - 1) >> maxLen);
	for(int i = 2; i < (1 << maxLen); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int len = 1 << (maxLen - 1); len > 0; len >>= 1) {
		W = w + len;
		int *PW = W + len;
		for(int i = 0; i < len; ++i)
			W[i] = PW[i << 1];
	}
}
void NTT(int len, int x[], int flag) {
	static int bitLen = 0, ivs = 1, bitRev[maxN];
	if(len != (1 << bitLen)) {
		const int inv2 = (mod + 1) >> 1;
		for(bitLen = 0, ivs = 1; (1 << bitLen) < len; ++bitLen, ivs = (LL)ivs * inv2 % mod);
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			swap(x[i], x[bitRev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0, *W = w + d + d; j < len; j += d << 1)
			for(int k = 0; k < d; ++k) {
				int t = (LL)W[k] * x[j + k + d] % mod;
				x[j + k + d] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		reverse(x + 1, x + len);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * ivs % mod;
	}
}
void solve1() { // O(n omega(n) + q omega(n) log n + q log v)
	// form test
	const int tot = 2;
	vector<int> pr = factorize(mod);
	assert(tot == (int)pr.size());
	for(int i = 0; i < m; ++i) {
		int x = i / 3, y = i % 3;
		Edge &cur = e[i];
		if(y == 0) {
			assert(cur.u == x + x + 1 && cur.v == x + x + 2 && cur.w == 1);
		} else if(y == 1) {
			assert(cur.u == x + x + 1 && cur.v == x + x + 3 && cur.w == 0);
		} else { // y == 2
			assert(cur.u == x + x + 2 && cur.v == x + x + 3 && cur.w == 0);
		}
	}
	const int maxw = maxew;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.u <= cur.v && cur.w < maxw);
	}
	// solve
	static int fact[tot + 1][maxw];
	for(int i = 0; i <= tot; ++i)
		fact[i][0] = i == tot;
	for(int i = 1; i < maxw; ++i) {
		int rem = i;
		for(int j = 0; j < tot; ++j) {
			int p = pr[j];
			for(fact[j][i] = fact[j][i - 1]; rem % p == 0; rem /= p, ++fact[j][i]);
		}
		fact[tot][i] = (LL)fact[tot][i - 1] * rem % mod;
	}
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		int u = cur.u, v = cur.v, w = cur.w;
		if(u == v) {
			ans[i] = !w;
			continue;
		}
		if(!(u & 1))
			++u;
		if(!(v & 1)) {
			--v;
			--w;
		}
		int dis = (v - u) / 2;
		if(w < 0 || dis < w) {
			ans[i] = 0;
			continue;
		}
		ans[i] = (LL)fact[tot][dis] * mod_inv((LL)fact[tot][w] * fact[tot][dis - w] % mod) % mod;
		for(int j = 0; j < tot; ++j)
			ans[i] = (LL)ans[i] * mod_pow(pr[j], fact[j][dis] - fact[j][w] - fact[j][dis - w]) % mod;
	}
}
void solve2() { // O(n w + q log q)
	// form test
	const int maxn = 101, maxw = maxew;
	assert(n < maxn && m == n + n - 1);
	for(int i = 0; i < m; ++i) {
		int x = i / 2, y = i % 2;
		Edge &cur = e[i];
		if(y == 0) {
			assert(cur.u == x + 1 && cur.v == x + 1 && cur.w < maxw);
		} else { // y == 1
			assert(cur.u == x + 1 && cur.v == x + 2 && cur.w == 0);
		}
	}
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.u == 1 && cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ord[maxq];
	for(int i = 0; i < q; ++i)
		ord[i] = i;
	sort(ord, ord + q, [&](int const &i, int const &j) {
		return que[i].v < que[j].v;
	});
	static int ways[maxw];
	ways[0] = 1;
	memset(ways + 1, 0, upp * sizeof(int));
	for(int i = 0, j = 0; i < n && j < q; ++i) {
		int w = e[i << 1].w;
		for(int x = w; x <= upp; ++x)
			mod_inc(ways[x], ways[x - w]);
		for( ; j < q && que[ord[j]].v == i + 1; ++j)
			ans[ord[j]] = ways[que[ord[j]].w];
	}
}
void solve3() { // O(n w + q w)
	// form test
	const int maxn = (int)1e4 + 1, maxw = (int)1e3 + 1;
	assert(n < maxn && m == n + n - 1);
	for(int i = 0; i < m; ++i) {
		int x = i / 2, y = i % 2;
		Edge &cur = e[i];
		if(y == 0) {
			assert(cur.u == x + 1 && cur.v == x + 1 && cur.w < maxw);
		} else { // y == 1
			assert(cur.u == x + 1 && cur.v == x + 2 && cur.w == 0);
		}
	}
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.u <= cur.v && cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ord[maxq];
	for(int i = 0; i < q; ++i)
		ord[i] = i;
	sort(ord, ord + q, [&](int const &i, int const &j) {
		return que[i].v < que[j].v;
	});
	static int ways[maxw], inv[maxn][maxw];
	ways[0] = inv[0][0] = 1;
	memset(ways + 1, 0, upp * sizeof(int));
	memset(inv[0] + 1, 0, upp * sizeof(int));
	for(int i = 0, j = 0; i < n && j < q; ++i) {
		int w = e[i << 1].w;
		for(int x = w; x <= upp; ++x)
			mod_inc(ways[x], ways[x - w]);
		memcpy(inv[i + 1], inv[i], (upp + 1) * sizeof(int));
		for(int x = w; x <= upp; ++x)
			mod_inc(inv[i + 1][x], mod - inv[i][x - w]);
		for( ; j < q && que[ord[j]].v == i + 1; ++j) {
			int &res = ans[ord[j]] = 0, *ivs = inv[que[ord[j]].u - 1];
			for(int x = 0, y = que[ord[j]].w; y >= 0; ++x, --y)
				mod_inc_mul(res, ways[x], ivs[y]);
		}
	}
}
void solve4() { // O(5^3 w log^2 w + q)
	// form test
	const int maxd = 5, maxw = maxew;
	NTT_init();
	for(int i = 0; i < m; ++i)
		assert(1 <= e[i].w && e[i].w < maxw);
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		assert(que[i].w < maxw);
		upp = max(upp, que[i].w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ways[maxd][maxd][maxew], sols[maxd][maxd][maxew];
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			memset(ways[i][j], 0, (upp + 1) * sizeof(int));
			memset(sols[i][j], 0, (upp + 1) * sizeof(int));
		}
		sols[i][i][0] = 1;
	}
	for(int i = 0; i < m; ++i)
		++ways[e[i].u - 1][e[i].v - 1][e[i].w];
	const int maxs = maxN;
	function<void(int, int)> calc = [&](int L, int R) {
		if(L >= R)
			return;
		int M = (L + R) >> 1;
		calc(L, M);
		int len, plen = R - L, qlen = M - L + 1;
		static int f[maxs], g[maxs];
		for(len = 1; len < plen; len <<= 1);
		assert(len < maxs);
		for(int x = 0; x < n; ++x)
			for(int y = 0; y < n; ++y)
				for(int z = 0; z < n; ++z) {
					memcpy(f, ways[x][y] + 1, plen * sizeof(int));
					memset(f + plen, 0, (len - plen) * sizeof(int));
					NTT(len, f, 1);
					memcpy(g, sols[y][z] + L, qlen * sizeof(int));
					memset(g + qlen, 0, (len - qlen) * sizeof(int));
					NTT(len, g, 1);
					for(int i = 0; i < len; ++i)
						f[i] = (LL)f[i] * g[i] % mod;
					NTT(len, f, -1);
					for(int i = M + 1, j = qlen - 1; i <= R; ++i, ++j)
						mod_inc(sols[x][z][i], f[j]);
				}
		calc(M + 1, R);
	};
	calc(0, upp);
	for(int i = 0; i < q; ++i)
		ans[i] = sols[que[i].u - 1][que[i].v - 1][que[i].w];
}
void solve5() { // O(10^3 s w)
	// form test
	const int maxd = 10, maxs = 401, maxw = 8001;
	assert(m % 2 == 0);
	int uppS = 0;
	for(int i = 0; (i << 1) < m; ++i) {
		Edge &lft = e[i << 1], &rht = e[i << 1 | 1];
		assert(lft.u <= maxd && lft.v == maxd + i + 1
			&& rht.u == maxd + i + 1 && rht.v <= maxd
			&& lft.w > 0 && rht.w > 0 && lft.w + rht.w < maxs);
		uppS = max(uppS, lft.w + rht.w);
	}
	int uppW = 0;
	for(int i = 0; i < q; ++i) {
		assert(que[i].w < maxw);
		uppW = max(uppW, que[i].w);
	}
	fprintf(stderr, "uppS %d uppW %d\n", uppS, uppW);
	// solve
	static int ways[maxd + 1][maxd + 1][maxs], sols[maxd + 1][maxd + 1][maxw];
	for(int i = 0; i < maxd; ++i) {
		for(int j = 0; j < maxd; ++j) {
			memset(ways[i][j], 0, (uppS + 1) * sizeof(int));
			memset(sols[i][j], 0, (uppW + 1) * sizeof(int));
		}
		sols[i][i][0] = 1;
	}
	for(int i = 0; (i << 1) < m; ++i) {
		Edge &lft = e[i << 1], &rht = e[i << 1 | 1];
		++ways[lft.u - 1][rht.v - 1][lft.w + rht.w];
	}
	for(int i = 2; i <= uppW; ++i)
		for(int x = 0; x < maxd; ++x)
			for(int y = 0; y < maxd; ++y)
				for(int j = 2, k = i - 2; j <= uppS && k >= 0; ++j, --k) {
					if(!ways[x][y][j])
						continue;
					for(int z = 0; z < maxd; ++z)
						mod_inc_mul(sols[x][z][i], ways[x][y][j], sols[y][z][k]);
				}
	for(int i = 0; i < q; ++i) {
		int u = que[i].u, v = que[i].v, w = que[i].w;
		if(!w) {
			ans[i] = u == v;
			continue;
		}
		if(u > maxd) {
			Edge &rht = e[(u - maxd - 1) << 1 | 1];
			u = rht.v;
			w -= rht.w;
		}
		if(v > maxd) {
			Edge &lft = e[(v - maxd - 1) << 1];
			v = lft.u;
			w -= lft.w;
		}
		ans[i] = w < 0 ? 0 : sols[u - 1][v - 1][w];
	}
}
void solve6() { // O(n^3 T log_T w + q n^2 log_T w + q log q log_T w), T = q / n
	// form test
	const int maxs = 200, BASE = 500, maxw = maxqw;
	assert(n == maxs && n * BASE == q);
	for(int i = 0; i < m; ++i)
		assert(e[i].w == 1);
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int o = 0, mat[3][maxs + 1][maxs + 1];
	static int ord[maxq], vec[maxq][maxs + 1];
	memset(mat[2], 0, sizeof mat[2]);
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		++mat[2][cur.u - 1][cur.v - 1];
	}
	memcpy(mat[o], mat[2], sizeof mat[2]);
	memset(vec, 0, sizeof vec);
	for(int i = 0; i < q; ++i) {
		vec[i][que[i].u - 1] = 1;
		ord[i] = i;
	}
	for(int step = 1; ; step *= BASE) {
		fprintf(stderr, "step %d\n", step);
		for(int i = 0; i < q; ++i)
			vec[i][maxs] = que[i].w / step % BASE;
		sort(ord, ord + q, [&](int const &x, int const &y) {
			return vec[x][maxs] < vec[y][maxs];
		});
		int pos = 0, lim = min(upp / step, BASE - 1);
		for( ; pos < q && !vec[ord[pos]][maxs]; ++pos);
		for(int i = 1; i <= lim; ++i) {
			for( ; pos < q && vec[ord[pos]][maxs] == i; ++pos) {
				int *row = vec[ord[pos]];
				static int res[maxs + 1];
				memset(res, 0, sizeof res);
				for(int x = 0; x <= maxs; ++x) {
					if(!row[x])
						continue;
					for(int y = 0; y <= maxs; ++y)
						mod_inc_mul(res[y], row[x], mat[o][x][y]);
				}
				memcpy(row, res, sizeof res);
			}
			o = !o;
			memset(mat[o], 0, sizeof mat[2]);
			for(int x = 0; x <= maxs; ++x)
				for(int y = 0; y <= maxs; ++y) {
					if(!mat[2][x][y])
						continue;
					for(int z = 0; z <= maxs; ++z)
						mod_inc_mul(mat[o][x][z], mat[2][x][y], mat[!o][y][z]);
				}
		}
		if(upp / step < BASE)
			break;
		memcpy(mat[2], mat[o], sizeof mat[2]);
	}
	for(int i = 0; i < q; ++i)
		ans[i] = vec[i][que[i].v - 1];
}
void solve7() { // O((d n)^3 T log_T w + q (d n)^2 log_T w + q log q log_T w), T = q / (d n), d = 2
	// form test
	const int maxd = 100, BASE = 500, maxw = maxqw;
	assert(n == maxd && (n + n) * BASE == q);
	for(int i = 0; i < m; ++i)
		assert(e[i].w <= 2);
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	const int maxs = maxd << 1;
	static int o = 0, mat[3][maxs + 1][maxs + 1];
	static int ord[maxq], vec[maxq][maxs + 1];
	memset(mat[2], 0, sizeof mat[2]);
	for(int i = 0; i < maxd; ++i)
		mat[2][maxd + i][i] = 1;
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		++mat[2][(2 - cur.w) * maxd + cur.u - 1][maxd + cur.v - 1];
	}
	memcpy(mat[o], mat[2], sizeof mat[2]);
	memset(vec, 0, sizeof vec);
	for(int i = 0; i < q; ++i) {
		vec[i][maxd + que[i].u - 1] = 1;
		ord[i] = i;
	}
	for(int step = 1; ; step *= BASE) {
		fprintf(stderr, "step %d\n", step);
		for(int i = 0; i < q; ++i)
			vec[i][maxs] = que[i].w / step % BASE;
		sort(ord, ord + q, [&](int const &x, int const &y) {
			return vec[x][maxs] < vec[y][maxs];
		});
		int pos = 0, lim = min(upp / step, BASE - 1);
		for( ; pos < q && !vec[ord[pos]][maxs]; ++pos);
		for(int i = 1; i <= lim; ++i) {
			for( ; pos < q && vec[ord[pos]][maxs] == i; ++pos) {
				int *row = vec[ord[pos]];
				static int res[maxs + 1];
				memset(res, 0, sizeof res);
				for(int x = 0; x <= maxs; ++x) {
					if(!row[x])
						continue;
					for(int y = 0; y <= maxs; ++y)
						mod_inc_mul(res[y], row[x], mat[o][x][y]);
				}
				memcpy(row, res, sizeof res);
			}
			o = !o;
			memset(mat[o], 0, sizeof mat[2]);
			for(int x = 0; x <= maxs; ++x)
				for(int y = 0; y <= maxs; ++y) {
					if(!mat[2][x][y])
						continue;
					for(int z = 0; z <= maxs; ++z)
						mod_inc_mul(mat[o][x][z], mat[2][x][y], mat[!o][y][z]);
				}
		}
		if(upp / step < BASE)
			break;
		memcpy(mat[2], mat[o], sizeof mat[2]);
	}
	for(int i = 0; i < q; ++i)
		ans[i] = vec[i][maxd + que[i].v - 1];
}
void solve8() { // O(n m + n^3 + (T + q) n log n log_T w), T = q
	// form test
	const int maxd = 1000, BASE = 10000, maxLen = 11, maxw = maxqw;
	assert(n == maxd && q == BASE);
	NTT_init(maxLen);
	for(int i = 0; i < m; ++i)
		assert(e[i].w == 1);
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.u == 1 && cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ways[maxd + 1][maxd + 1], poly[maxd + 1][maxd + 1];
	static int ord[BASE + 1], vec[BASE + 1][maxd + 1];
	memset(ways, 0, sizeof ways);
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		++ways[cur.u - 1][cur.v - 1];
	}
	for(int i = 0; i + 1 < maxd; ++i) {
		for(int j = i + 1; j < maxd; ++j)
			if(ways[j][i]) {
				for(int k = i; k < maxd; ++k)
					swap(ways[i + 1][k], ways[j][k]);
				for(int k = 0; k < maxd; ++k)
					swap(ways[k][j], ways[k][i + 1]);
				break;
			}
		if(!ways[i + 1][i])
			continue;
		int ivs = mod_inv(ways[i + 1][i]);
		for(int j = i + 2; j < maxd; ++j) {
			if(!ways[j][i])
				continue;
			int prd = (LL)ways[j][i] * ivs % mod;
			for(int k = i; k < maxd; ++k)
				mod_inc_mul(ways[j][k], mod - prd, ways[i + 1][k]);
			for(int k = 0; k < maxd; ++k)
				mod_inc_mul(ways[k][i + 1], prd, ways[k][j]);
		}
	}
	poly[maxd][0] = 1;
	for(int i = maxd - 1; i >= 0; --i) {
		poly[i][0] = 0;
		memcpy(poly[i] + 1, poly[i + 1], (maxd - i) * sizeof(int));
		if(ways[i][i])
			for(int j = 0; j < maxd - i; ++j)
				mod_inc_mul(poly[i][j], mod - ways[i][i], poly[i + 1][j]);
		int prd = 1;
		for(int j = i + 1; j < maxd && ways[j][j - 1]; ++j) {
			prd = (LL)prd * ways[j][j - 1] % mod;
			int coeff = (LL)prd * (mod - ways[i][j]) % mod;
			if(!coeff)
				continue;
			for(int k = 0; k < maxd - j; ++k)
				mod_inc_mul(poly[i][k], coeff, poly[j + 1][k]);
		}
	}
	memset(ways, 0, sizeof ways);
	ways[0][0] = 1;
	for(int i = 1; i <= maxd; ++i)
		for(int j = 0; j < m; ++j) {
			Edge &cur = e[j];
			mod_inc(ways[i][cur.v - 1], ways[i - 1][cur.u - 1]);
		}
	/* verification
	for(int i = 0; i < maxd; ++i) {
		int sum = 0;
		for(int j = 0; j <= maxd; ++j)
			mod_inc_mul(sum, poly[0][j], ways[j][i]);
		assert(!sum);
	}
	*/
	const int maxs = 1 << maxLen | 1;
	auto polyMul = [&](int aLen, int a[], int bLen, int b[], int cLen, int c[]) {
		int len, plen = aLen + bLen - 1;
		static int f[maxs], g[maxs];
		for(len = 1; len < plen; len <<= 1);
		assert(cLen <= plen && len < maxs);
		memcpy(f, a, aLen * sizeof(int));
		memset(f + aLen, 0, (len - aLen) * sizeof(int));
		NTT(len, f, 1);
		memcpy(g, b, bLen * sizeof(int));
		memset(g + bLen, 0, (len - bLen) * sizeof(int));
		NTT(len, g, 1);
		for(int i = 0; i < len; ++i)
			f[i] = (LL)f[i] * g[i] % mod;
		NTT(len, f, -1);
		memcpy(c, f, cLen * sizeof(int));
	};
	// deg(poly[0]) = maxd, deg(poly[1]) = maxd - 2
	assert(poly[0][maxd] == 1);
	poly[1][0] = 1;
	for(int i = 1; i < maxd - 1; ++i) {
		int sum = 0;
		for(int j = 0; j < i; ++j)
			mod_inc_mul(sum, poly[1][j], poly[0][maxd - i + j]);
		poly[1][i] = sum ? mod - sum : 0;
	}
	auto polyMerge = [&](int f[maxd + 1], int g[maxd + 1]) { // f = f * g % poly[0], (f, g != poly[0-2])
		static int tmp[maxd << 1 | 1];
		polyMul(maxd, f, maxd, g, maxd + maxd - 1, tmp);
		reverse(tmp, tmp + maxd + maxd - 1);
		polyMul(maxd - 1, tmp, maxd - 1, poly[1], maxd - 1, poly[2]);
		reverse(poly[2], poly[2] + maxd - 1);
		polyMul(maxd, poly[0], maxd - 1, poly[2], maxd, f);
		reverse(tmp, tmp + maxd + maxd - 1);
		for(int i = 0; i < maxd; ++i)
			(f[i] = tmp[i] - f[i]) < 0 && (f[i] += mod);
	};
	// deg(vec[i]) = deg(poly[3]) = deg(poly[4]) = maxd - 1
	for(int i = 0; i < q; ++i) {
		memset(vec[i], 0, maxd * sizeof(int));
		vec[i][que[i].w % maxd] = 1;
		ord[i] = i;
	}
	for(int i = 0; i < maxd; ++i)
		poly[3][i] = poly[0][i] ? mod - poly[0][i] : 0;
	memcpy(poly[4], poly[3], maxd * sizeof(int));
	for(int step = maxd; ; step *= BASE) {
		fprintf(stderr, "step %d\n", step);
		for(int i = 0; i < q; ++i)
			vec[i][maxd] = que[i].w / step % BASE;
		sort(ord, ord + q, [&](int const &x, int const &y) {
			return vec[x][maxd] < vec[y][maxd];
		});
		int pos = 0, lim = min(upp / step, BASE - 1);
		for( ; pos < q && !vec[ord[pos]][maxd]; ++pos);
		for(int i = 1; i <= lim; ++i) {
			for( ; pos < q && vec[ord[pos]][maxd] == i; ++pos)
				polyMerge(vec[ord[pos]], poly[4]);
			polyMerge(poly[4], poly[3]);
		}
		if(upp / step < BASE)
			break;
		memcpy(poly[3], poly[4], maxd * sizeof(int));
	}
	for(int i = 0; i < q; ++i) {
		ans[i] = 0;
		for(int j = 0; j < maxd; ++j)
			mod_inc_mul(ans[i], vec[i][j], ways[j][que[i].v - 1]);
	}
}
void solve9() { // O(b^3 d^2 + b^3 w / d + q b^2)
	// form test
	const int maxd = 1000, maxb = 10, maxw = (int)1e5 + 1;
	assert(n == maxd * maxb);
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		assert((cur.u + 1) % maxd == cur.v % maxd && cur.w == 1);
	}
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		int dis = cur.v % maxd - cur.u % maxd;
		if(dis < 0)
			dis += maxd;
		assert(max(dis, 1) <= cur.w && cur.w % maxd == dis && (cur.w - dis) / maxd < maxw);
		upp = max(upp, (cur.w - dis) / maxd);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ways[maxd + 1][maxb + 1][maxb + 1], o = 0, mat[3][maxb + 1][maxb + 1];
	static int tot, ord[maxq], pre[maxd + 1][maxb + 1][maxb + 1], suf[maxd + 1][maxb + 1][maxb + 1];
	memset(ways, 0, sizeof ways);
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		int j = (cur.u - 1) % maxd, u = (cur.u - 1) / maxd, v = (cur.v - 1) / maxd;
		++ways[j][u][v];
	}
	memset(pre, 0, sizeof pre);
	memset(suf, 0, sizeof suf);
	for(int i = 0; i < maxb; ++i)
		pre[0][i][i] = suf[0][i][i] = 1;
	for(int i = 1, j = 0; i != 0; j = i, i = (i + 1) % maxd)
		for(int x = 0; x < maxb; ++x)
			for(int y = 0; y < maxb; ++y) {
				if(!pre[j][x][y])
					continue;
				for(int z = 0; z < maxb; ++z)
					mod_inc_mul(pre[i][x][z], pre[j][x][y], ways[j][y][z]);
			}
	for(int i = maxd - 1, j = 0; i != 0; j = i, i = (i - 1) % maxd)
		for(int x = 0; x < maxb; ++x)
			for(int y = 0; y < maxb; ++y) {
				if(!ways[i][x][y])
					continue;
				for(int z = 0; z < maxb; ++z)
					mod_inc_mul(suf[i][x][z], ways[i][x][y], suf[j][y][z]);
			}
	memset(mat[2], 0, sizeof mat[2]);
	for(int x = 0; x < maxb; ++x)
		for(int y = 0; y < maxb; ++y) {
			if(!ways[0][x][y])
				continue;
			for(int z = 0; z < maxb; ++z)
				mod_inc_mul(mat[2][x][z], ways[0][x][y], suf[1][y][z]);
		}
	tot = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		int x = (cur.u - 1) % maxd, y = (cur.v - 1) % maxd;
		cur.w -= (x ? maxd - x : 0) + y;
		if(que[i].w < 0)
			ord[tot++] = i;
	}
	sort(ord, ord + tot, [&](int const &x, int const &y) {
		return make_pair((que[x].u - 1) % maxd, (que[x].v - 1) % maxd)
			< make_pair((que[y].u - 1) % maxd, (que[y].v - 1) % maxd);
	});
	for(int i = 0, L = 0; i < tot && L < maxd; ) {
		L = max(L, (que[ord[i]].u - 1) % maxd);
		memcpy(mat[o], pre[0], sizeof mat[2]);
		for(int R = L; i < tot && (que[ord[i]].u - 1) % maxd == L; ++i) {
			for( ; R != (que[ord[i]].v - 1) % maxd; R = (R + 1) % maxd) {
				o = !o;
				memset(mat[o], 0, sizeof mat[2]);
				for(int x = 0; x < maxb; ++x)
					for(int y = 0; y < maxb; ++y) {
						if(!mat[!o][x][y])
							continue;
						for(int z = 0; z < maxb; ++z)
							mod_inc_mul(mat[o][x][z], mat[!o][x][y], ways[R][y][z]);
					}
			}
			int j = ord[i];
			Edge &cur = que[j];
			ans[j] = mat[o][(cur.u - 1) / maxd][(cur.v - 1) / maxd];
		}
	}
	tot = 0;
	for(int i = 0; i < q; ++i)
		if(que[i].w >= 0)
			ord[tot++] = i;
	sort(ord, ord + tot, [&](int const &x, int const &y) {
		return que[x].w < que[y].w;
	});
	memcpy(mat[o], pre[0], sizeof mat[2]);
	for(int i = 0, j = 0; i < tot; ++i) {
		for( ; j + maxd <= que[ord[i]].w; j += maxd) {
			o = !o;
			memset(mat[o], 0, sizeof mat[2]);
			for(int x = 0; x < maxb; ++x)
				for(int y = 0; y < maxb; ++y) {
					if(!mat[2][x][y])
						continue;
					for(int z = 0; z < maxb; ++z)
						mod_inc_mul(mat[o][x][z], mat[2][x][y], mat[!o][y][z]);
				}
		}
		Edge &cur = que[ord[i]];
		int ux = (cur.u - 1) % maxd, uy = (cur.u - 1) / maxd;
		int vx = (cur.v - 1) % maxd, vy = (cur.v - 1) / maxd;
		static int vec[maxb + 1];
		memset(vec, 0, sizeof vec);
		for(int x = 0; x < maxb; ++x) {
			if(!suf[ux][uy][x])
				continue;
			for(int y = 0; y < maxb; ++y)
				mod_inc_mul(vec[y], suf[ux][uy][x], mat[o][x][y]);
		}
		int &res = ans[ord[i]] = 0;
		for(int x = 0; x < maxb; ++x)
			mod_inc_mul(res, vec[x], pre[vx][x][vy]);
	}
}
void solve10() { // O(n m + n^3 + (T + q) n log n log_T w), T = q
	// form test
	const int maxd = 3000, BASE = 10000, maxLen = 13, maxw = maxqw;
	assert(n == maxd && q == BASE);
	NTT_init(maxLen);
	for(int i = 0; i < m; ++i)
		assert(e[i].w == 1);
	int upp = 0;
	for(int i = 0; i < q; ++i) {
		Edge &cur = que[i];
		assert(cur.u == 1 && cur.w < maxw);
		upp = max(upp, cur.w);
	}
	fprintf(stderr, "upp %d\n", upp);
	// solve
	static int ways[maxd + 1][maxd + 1], poly[maxd + 1][maxd + 1];
	static int ord[BASE + 1], vec[BASE + 1][maxd + 1];
	memset(ways, 0, sizeof ways);
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[i];
		++ways[cur.u - 1][cur.v - 1];
	}
	for(int i = 0; i + 1 < maxd; ++i) {
		for(int j = i + 1; j < maxd; ++j)
			if(ways[j][i]) {
				for(int k = i; k < maxd; ++k)
					swap(ways[i + 1][k], ways[j][k]);
				for(int k = 0; k < maxd; ++k)
					swap(ways[k][j], ways[k][i + 1]);
				break;
			}
		if(!ways[i + 1][i])
			continue;
		int ivs = mod_inv(ways[i + 1][i]);
		for(int j = i + 2; j < maxd; ++j) {
			if(!ways[j][i])
				continue;
			int prd = (LL)ways[j][i] * ivs % mod;
			for(int k = i; k < maxd; ++k)
				mod_inc_mul(ways[j][k], mod - prd, ways[i + 1][k]);
			for(int k = 0; k < maxd; ++k)
				mod_inc_mul(ways[k][i + 1], prd, ways[k][j]);
		}
	}
	poly[maxd][0] = 1;
	for(int i = maxd - 1; i >= 0; --i) {
		poly[i][0] = 0;
		memcpy(poly[i] + 1, poly[i + 1], (maxd - i) * sizeof(int));
		if(ways[i][i])
			for(int j = 0; j < maxd - i; ++j)
				mod_inc_mul(poly[i][j], mod - ways[i][i], poly[i + 1][j]);
		int prd = 1;
		for(int j = i + 1; j < maxd && ways[j][j - 1]; ++j) {
			prd = (LL)prd * ways[j][j - 1] % mod;
			int coeff = (LL)prd * (mod - ways[i][j]) % mod;
			if(!coeff)
				continue;
			for(int k = 0; k < maxd - j; ++k)
				mod_inc_mul(poly[i][k], coeff, poly[j + 1][k]);
		}
	}
	memset(ways, 0, sizeof ways);
	ways[0][0] = 1;
	for(int i = 1; i <= maxd; ++i)
		for(int j = 0; j < m; ++j) {
			Edge &cur = e[j];
			mod_inc(ways[i][cur.v - 1], ways[i - 1][cur.u - 1]);
		}
	/* verification
	for(int i = 0; i < maxd; ++i) {
		int sum = 0;
		for(int j = 0; j <= maxd; ++j)
			mod_inc_mul(sum, poly[0][j], ways[j][i]);
		assert(!sum);
	}
	*/
	const int maxs = 1 << maxLen | 1;
	auto polyMul = [&](int aLen, int a[], int bLen, int b[], int cLen, int c[]) {
		int len, plen = aLen + bLen - 1;
		static int f[maxs], g[maxs];
		for(len = 1; len < plen; len <<= 1);
		assert(cLen <= plen && len < maxs);
		memcpy(f, a, aLen * sizeof(int));
		memset(f + aLen, 0, (len - aLen) * sizeof(int));
		NTT(len, f, 1);
		memcpy(g, b, bLen * sizeof(int));
		memset(g + bLen, 0, (len - bLen) * sizeof(int));
		NTT(len, g, 1);
		for(int i = 0; i < len; ++i)
			f[i] = (LL)f[i] * g[i] % mod;
		NTT(len, f, -1);
		memcpy(c, f, cLen * sizeof(int));
	};
	// deg(poly[0]) = maxd, deg(poly[1]) = maxd - 2
	assert(poly[0][maxd] == 1);
	poly[1][0] = 1;
	for(int i = 1; i < maxd - 1; ++i) {
		int sum = 0;
		for(int j = 0; j < i; ++j)
			mod_inc_mul(sum, poly[1][j], poly[0][maxd - i + j]);
		poly[1][i] = sum ? mod - sum : 0;
	}
	auto polyMerge = [&](int f[maxd + 1], int g[maxd + 1]) { // f = f * g % poly[0], (f, g != poly[0-2])
		static int tmp[maxd << 1 | 1];
		polyMul(maxd, f, maxd, g, maxd + maxd - 1, tmp);
		reverse(tmp, tmp + maxd + maxd - 1);
		polyMul(maxd - 1, tmp, maxd - 1, poly[1], maxd - 1, poly[2]);
		reverse(poly[2], poly[2] + maxd - 1);
		polyMul(maxd, poly[0], maxd - 1, poly[2], maxd, f);
		reverse(tmp, tmp + maxd + maxd - 1);
		for(int i = 0; i < maxd; ++i)
			(f[i] = tmp[i] - f[i]) < 0 && (f[i] += mod);
	};
	// deg(vec[i]) = deg(poly[3]) = deg(poly[4]) = maxd - 1
	for(int i = 0; i < q; ++i) {
		memset(vec[i], 0, maxd * sizeof(int));
		vec[i][que[i].w % maxd] = 1;
		ord[i] = i;
	}
	for(int i = 0; i < maxd; ++i)
		poly[3][i] = poly[0][i] ? mod - poly[0][i] : 0;
	memcpy(poly[4], poly[3], maxd * sizeof(int));
	for(int step = maxd; ; step *= BASE) {
		fprintf(stderr, "step %d\n", step);
		for(int i = 0; i < q; ++i)
			vec[i][maxd] = que[i].w / step % BASE;
		sort(ord, ord + q, [&](int const &x, int const &y) {
			return vec[x][maxd] < vec[y][maxd];
		});
		int pos = 0, lim = min(upp / step, BASE - 1);
		for( ; pos < q && !vec[ord[pos]][maxd]; ++pos);
		for(int i = 1; i <= lim; ++i) {
			for( ; pos < q && vec[ord[pos]][maxd] == i; ++pos)
				polyMerge(vec[ord[pos]], poly[4]);
			polyMerge(poly[4], poly[3]);
		}
		if(upp / step < BASE)
			break;
		memcpy(poly[3], poly[4], maxd * sizeof(int));
	}
	for(int i = 0; i < q; ++i) {
		ans[i] = 0;
		for(int j = 0; j < maxd; ++j)
			mod_inc_mul(ans[i], vec[i][j], ways[j][que[i].v - 1]);
	}
}
int main() {
	for(int Case = 1; Case <= 10; ++Case) {
		static char buf[1 << 10 | 1];
		sprintf(buf, "noip%d.in", Case);
		FILE *fin = fopen(buf, "r");
		assert(fscanf(fin, "%d%d%d%d", &n, &m, &q, &mod) == 4
			&& 1 <= n && n < maxn && 1 <= m && m < maxm
			&& 1 <= q && q < maxq && 1 <= mod && mod < maxp);
		for(int i = 0; i < m + q; ++i) {
			Edge &cur = i < m ? e[i] : que[i - m];
			const int &maxw = i < m ? maxew : maxqw;
			assert(fscanf(fin, "%d%d%d", &cur.u, &cur.v, &cur.w) == 3
				&& 1 <= cur.u && cur.u <= n && 1 <= cur.v && cur.v <= n
				&& 0 <= cur.w && cur.w < maxw);
		}
		memset(ans, -1, q * sizeof(int));
		static void (*solve[])() = {NULL,
			solve1, solve2, solve3, solve4, solve5,
			solve6, solve7, solve8, solve9, solve10};
		clock_t t1 = clock();
		solve[Case]();
		fprintf(stderr, "time consumed: %lld ms\n", (LL)(clock() - t1));
		fclose(fin);
		bool flag = 0;
		for(int i = 0; i < q && !flag; ++i)
			flag |= ans[i] == -1;
		if(flag) {
			fprintf(stderr, "Case #%d: halted!\n", Case);
			continue;
		}
		sprintf(buf, "noip%d.out", Case);
		FILE *fout = fopen(buf, "w");
		for(int i = 0; i < q; ++i)
			fprintf(fout, "%d\n", ans[i]);
		fclose(fout);
		fprintf(stderr, "Case #%d: finished!\n", Case);
	}
	return 0;
}
