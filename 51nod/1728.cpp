#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxlen = 22, maxm = 1 << maxlen, mod = 985661441, gen = 3; // maxn << 1 <= maxm
const int maxn = 2000000 + 1, maxk = 4, maxo = (maxn * 3 >> 1) + maxm + maxk;

int inv[maxn], fact[maxn];
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (int)((LL)x * x % mod))
		if(k & 1)
			ret = (int)((LL)ret * x % mod);
	return ret;
}
inline int mod_inv(int x)
{
	return x < maxn ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int w[maxm], inv2[maxlen + 1];
inline int mod_add(int x, int y)
{
	return x + y >= mod ? x + y - mod : x + y;
}
inline int mod_sub(int x, int y)
{
	return x - y < 0 ? x - y + mod : x - y;
}
inline void NTT(int len, int x[], bool flag)
{
	for(int i = 0, j = 0; i < len; ++i)
	{
		if(i > j)
			std::swap(x[i], x[j]);
		for(int l = len >> 1; (j ^= l) < l; l >>= 1);
	}
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0; k < d; ++k)
			{
				int t = (LL)w[(maxm >> i) * k] * x[j + k + d] % mod;
				x[j + d + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag)
	{
		std::reverse(x + 1, x + len);
		int bitLen = 0;
		for( ; 1 << bitLen < len; ++bitLen);
		int val = inv2[bitLen];
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
// poly inv, log, exp
void PolyInvIterate(int n, int cur[], int len, int nxt[maxm])
{
	// REQUIRES: NXT = CUR^(-1) (mod x^(len/2)), NXT[len/2 : len] is any number
	// EFFECTS : NXT = CUR^(-1) (mod x^len), NXT[len : len*2] is any number
	static int tmp[maxm];
	// before here, nxt = CUR^(-1) (mod x^(len/2)), nxt[len/2 : len] is any number
	int lim = std::min(n, len);
	// tmp = CUR (mod x^min(n,len)) -> tmp (mod x^(len*2))
	memcpy(tmp, cur, lim * sizeof(int));
	memset(tmp + lim, 0, ((len << 1) - lim) * sizeof(int));
	NTT(len << 1, tmp, 0);
	// nxt (mod x^(len/2)) -> nxt (mod x^(len*2))
	memset(nxt + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
	NTT(len << 1, nxt, 0);
	// nxt = (2 - CUR * nxt) * nxt (mod x^len), nxt[len : len * 2] is any number
	for(int i = 0; i < len << 1; ++i)
		if((nxt[i] = (2 - (LL)tmp[i] * nxt[i]) % mod * nxt[i] % mod) < 0)
			nxt[i] += mod;
	NTT(len << 1, nxt, 1);
}
void PolyInv(int n, int cur[], int nxt[maxm])
{
	// REQUIRES: CUR is a poly mod x^n
	// EFFECTS : NXT = CUR^(-1) (mod x^(len/2)), NXT[len/2 : len] is any number, len >= n * 2
	int len;
	// nxt = CUR^(-1) (mod x)
	nxt[0] = mod_inv(cur[0]);
	// iteration
	for(len = 2; (len >> 1) < n; len <<= 1)
		PolyInvIterate(n, cur, len, nxt);
}
void PolyInvHis(int n, int cur[], int nxt[maxm])
{
	static int cur_i = 0, pre_i = 1, len, seq[2][maxm];
	if(n == 2)
	{
		seq[cur_i][0] = mod_inv(cur[0]);
		for(len = 2; (len >> 1) < n; len <<= 1)
		{
			cur_i ^= 1;
			pre_i ^= 1;
			memcpy(seq[cur_i], seq[pre_i], (len >> 1) * sizeof(int));
			PolyInvIterate(n, cur, len, seq[cur_i]);
		}
	}
	else
	{
		cur_i ^= 1;
		pre_i ^= 1;
		for(len >>= 1; (len >> 1) < n; len <<= 1)
		{
			cur_i ^= 1;
			pre_i ^= 1;
			memcpy(seq[cur_i], seq[pre_i], (len >> 1) * sizeof(int));
			PolyInvIterate(n, cur, len, seq[cur_i]);
		}
	}
	memcpy(nxt, seq[cur_i], len * sizeof(int));
}
void PolyLog(int n, int cur[], int nxt[maxm])
{
	 // EFFECTS: NXT = logCUR, NXT[n : len] is any number, len >= n * 2
	int len = 1;
	for( ; len < n << 1; len <<= 1);
	static int tmp[maxm];
	// tmp = CUR^(-1) (value) (mod x^(len/2)), tmp[len/2 : len] is any number
	PolyInvHis(n, cur, tmp);
	// tmp (mod x^(len/2)) -> tmp (mod x^len)
	memset(tmp + (len >> 1), 0, (len >> 1) * sizeof(int));
	NTT(len, tmp, 0);
	// nxt = CUR' (mod x^n) -> nxt (mod x^len)
	for(int i = 0; i + 1 < n; ++i)
		nxt[i] = cur[i + 1] * (i + 1LL) % mod;
	nxt[n - 1] = 0;
	memset(nxt + (n - 1), 0, (len - (n - 1)) * sizeof(int));
	NTT(len, nxt, 0);
	// nxt = CUR' / CUR (mod x^(len/2)), nxt[len/2 : len] is any number
	for(int i = 0; i < len; ++i)
		nxt[i] = (LL)nxt[i] * tmp[i] % mod;
	NTT(len, nxt, 1);
	// nxt = NXT (mod x^n), nxt[n : len] is any number
	for(int i = n - 1; i > 0; --i)
		nxt[i] = (LL)nxt[i - 1] * inv[i] % mod;
	nxt[0] = 0;
}
void PolyExp(int n, int cur[], int nxt[])
{
	// EFFECTS: NXT = e^CUR, NXT[n : len] is any number, len >= n * 2
	int len;
	static int tmp[maxm];
	nxt[0] = 1;
	for(len = 2; (len >> 1) < n; len <<= 1)
	{
		// before here, nxt = e^CUR (mod x^(len/2)), nxt[len/2 : len] is any number
		// nxt (mod x^(len/2)) -> nxt (mod x^(len*2))
		memset(nxt + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		// tmp = logNXT (mod x^len), tmp[len : len * 2] is any number
		PolyLog(len, nxt, tmp);
		// tmp = 1 - logNXT + CUR (mod x^len)
		if(--tmp[0] < 0)
			tmp[0] += mod;
		for(int i = 0; i < len; ++i)
			if((tmp[i] = (i < n ? cur[i] : 0) - tmp[i]) < 0)
				tmp[i] += mod;
		// tmp (mod x^len) -> tmp (mod x^(len*2))
		memset(tmp + len, 0, len * sizeof(int));
		NTT(len << 1, tmp, 0);
		NTT(len << 1, nxt, 0);
		// nxt = NXT (1 - logNXT + CUR) (mod x^len), nxt[len : len * 2] is any number
		for(int i = 0; i < len << 1; ++i)
			nxt[i] = (LL)nxt[i] * tmp[i] % mod;
		NTT(len << 1, nxt, 1);
	}
}
int pool[maxo], *f[maxk], sz[maxk];
int main()
{
	// NTT init
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxlen); // make sure that mod = 2 ^ maxlen * k + 1
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxlen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	// poly init
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	f[1] = pool + 1;
	sz[1] = maxn;
	f[1][0] = 1;
	for(int i = 1; i < maxn; ++i)
		f[1][i] = (LL)f[1][i - 1] * inv[i] % mod;
	// poly NTT
	for(int i = 2; i < maxk; ++i)
	{
		f[i] = f[i - 1] + sz[i - 1] + 1;
		sz[i] = (maxn - 1) / i + 1;
		PolyExp(sz[i], f[i - 1] - 1, f[i]);
	}
	// poly output
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	for(int i = 1; i < maxk; ++i)
		for(int j = i; j < sz[i]; ++j)
			f[i][j] = (LL)f[i][j] * fact[j] % mod;
	int t, s, k;
	scanf("%d", &t); // read(t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &s, &k); // read(s), read(k);
		k = k < s ? k : s;
		printf("Case #%d: %d\n", Case, f[k][s]); // print("Case #"), print(Case), print(": "), println(f[k][s]);
	}
	return 0;
}
