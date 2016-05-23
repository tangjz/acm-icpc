#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxd = 17, maxn = 1 << maxd - 1;
int n, mod, ori, inv[maxn + 1], sz, tot, w[maxd], *f, *g[maxn << 1], ans;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int mod_inv(int x)
{
	return x <= maxn ? inv[x] : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int x[maxn], y[maxn];
void NTT(int len, int x[], int flag)
{
	static int bitlen, bitrev[maxn];
	for(bitlen = 0; 1 << bitlen < len; ++bitlen);
	for(int i = 1; i < len; ++i)
	{
		bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitlen - 1));
		if(i < bitrev[i])
			std::swap(x[i], x[bitrev[i]]);
	}
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = j, ww = 1; k < j + d; ++k)
			{
				int t = (LL)ww * x[k + d] % mod;
				if((x[k + d] = x[k] - t) < 0)
					x[k + d] += mod;
				if((x[k] = x[k] - mod + t) < 0)
					x[k] += mod;
				ww = (LL)ww * w[i] % mod;
			}
	if(flag)
	{
		std::reverse(x + 1, x + len);
		int inv = mod_pow(mod + 1 >> 1, bitlen);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv % mod;
	}
}
void polyInv(int n, int cur[], int nxt[]) // NXT = CUR^(-1)
{
	if(n == 1)
	{
		nxt[0] = mod_inv(cur[0]);
		return;
	}
	int len = 1, plen = n + 1 >> 1;
	for( ; len < n << 1; len <<= 1);
	polyInv(plen, cur, nxt); // nxt = CUR^(-1) (mod x^(n/2))
	memset(nxt + plen, 0, (len - plen) * sizeof(int));
	static int tmp[maxn];
	memcpy(tmp, cur, n * sizeof(int));
	memset(tmp + n, 0, (len - n) * sizeof(int)); // tmp = CUR
	NTT(len, tmp, 0);
	NTT(len, nxt, 0);
	for(int i = 0; i < len; ++i)
	{
		int temp = (LL)tmp[i] * nxt[i] % mod;
		temp = 2 < temp ? 2 - temp + mod : 2 - temp;
		nxt[i] = (LL)temp * nxt[i] % mod; // nxt = (2 - CUR * nxt) * nxt
	}
	NTT(len, nxt, 1); // nxt = CUR^(-1) (mod x^n)
}
void polyDiv(int n, int a[], int m, int b[], int d[], int r[])
{
	if(n < m)
	{
		d[0] = 0;
		memcpy(r, a, n * sizeof(int));
		return;
	}
	int len = 1, plen = n - m + 1;
	for( ; len < plen << 1; len <<= 1);
	memcpy(x, b, m * sizeof(int));
	std::reverse(x, x + m);
	if(m < len)
		memset(x + m, 0, (len - m) * sizeof(int));
	polyInv(plen, x, y);
	memset(y + plen, 0, (len - plen) * sizeof(int));
	NTT(len, y, 0);
	memcpy(x, a, n * sizeof(int));
	std::reverse(x, x + n);
	memset(x + plen, 0, (len - plen) * sizeof(int));
	NTT(len, x, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, 1);
	std::reverse(x, x + plen);
	memcpy(d, x, plen * sizeof(int));
	for(len = 1; len < n; len <<= 1);
	memset(x + plen, 0, (len - plen) * sizeof(int));
	NTT(len, x, 0);
	memcpy(y, b, m * sizeof(int));
	memset(y + m, 0, (len - m) * sizeof(int));
	NTT(len, y, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, 1);
	for(int i = 0; i < m; ++i)
		r[i] = a[i] - x[i] < 0 ? a[i] - x[i] + mod : a[i] - x[i];
}
static int pool[maxn * maxd << 1], *tail = pool;
inline int* tail_alloc(int len)
{
	int *ret = tail;
	tail += len;
	return ret;
}
inline void tail_free(int len)
{
	tail -= len;
	memset(tail, 0, len * sizeof(int));
}
inline int round_2(int x)
{
	static int ret;
	for(ret = 1; ret < x; ret <<= 1);
	return ret;
}
void init_f(int L, int R, int *rt)
{
	if(L == R)
	{
		rt[0] = L;
		rt[1] = 1;
		return;
	}
	int M = L + R >> 1, size = R - L + 2, szL = M - L + 2, szR = R - M + 1, len = round_2(size);
	int *lch = tail_alloc(szL);
	init_f(L, M, lch);
	int *rch = tail_alloc(szR);
	init_f(M + 1, R, rch);
	memcpy(x, lch, szL * sizeof(int));
	memset(x + szL, 0, (len - szL) * sizeof(int));
	NTT(len, x, 0);
	memcpy(y, rch, szR * sizeof(int));
	memset(y + szR, 0, (len - szR) * sizeof(int));
	NTT(len, y, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, 1);
	memcpy(rt, x, size * sizeof(int));
	tail_free(tail - rt - size);
}
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void init_g(int L, int R)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		g[o] = tail_alloc(2);
		g[o][0] = mod - L * sz;
		g[o][1] = 1;
		return;
	}
	int M = L + R >> 1, size = R - L + 2, szL = M - L + 2, szR = R - M + 1;
	int lch = seg_idx(L, M), rch = seg_idx(M + 1, R), len = round_2(size + 1);
	init_g(L, M);
	init_g(M + 1, R);
	memcpy(x, g[lch], szL * sizeof(int));
	memset(x + szL, 0, (len - szL) * sizeof(int));
	NTT(len, x, 0);
	memcpy(y, g[rch], szR * sizeof(int));
	memset(y + szR, 0, (len - szR) * sizeof(int));
	NTT(len, y, 0);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, 1);
	g[o] = tail_alloc(size);
	memcpy(g[o], x, size * sizeof(int));
}
void solve(int L, int R, int *poly, int deg)
{
	int size = R - L + 1, *rt = tail_alloc(size);
	static int tmp[maxn];
	polyDiv(deg, poly, R - L + 2, g[seg_idx(L, R)], tmp, rt);
	if(L == R)
	{
		ans = (LL)ans * rt[0] % mod;
		return;
	}
	for( ; size > 1 && !rt[size - 1]; --size);
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	solve(L, M, rt, size);
	solve(M + 1, R, rt, size);
	tail_free(tail - rt);
}
int main()
{
	scanf("%d%d", &n, &mod);
	if(n >= mod)
	{
		puts("0");
		return 0;
	}
	inv[1] = 1;
	for(int i = 2; i <= maxn; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	for(ori = 2; ; ++ori)
	{
		int len = mod - 1;
		bool flag = 1;
		for(int i = 2; i * i <= len; ++i)
			if(len % i == 0)
			{
				if(mod_pow(ori, (mod - 1) / i) == 1)
				{
					flag = 0;
					break;
				}
				for(len /= i; len % i == 0; len /= i);
			}
		if(flag)
			break;
	}
	for(sz = 0; sz * sz <= n; ++sz);
	--sz;
	int bitlen = 1;
	for( ; 1 << bitlen <= sz; ++bitlen);
	w[bitlen] = mod_pow(ori, mod - 1 >> bitlen);
	for(int i = bitlen - 1; i >= 0; --i)
		w[i] = (LL)w[i + 1] * w[i + 1] % mod;
	ans = 1;
	for(int i = sz * sz + 1; i <= n; ++i)
		ans = (LL)ans * i % mod;
	init_f(1, sz, f = tail_alloc(sz + 1));
	init_g(0, sz - 1);
	solve(0, sz - 1, f, sz + 1);
	if(n & 1)
		ans = (LL)ans * inv[2] % mod;
	printf("%d\n", ans);
	return 0;
}
