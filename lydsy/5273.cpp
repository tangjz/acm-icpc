#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxe = 7, mod = 998244353;
const int maxLen = 18, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs], A[maxs], B[maxs];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << (bitLen - 1));
	W[0] = 1;
	W[1] = mod_pow(gen, (mod - 1) >> bitLen);
	for(int i = 2; i < (1 << (bitLen - 1)); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << (bitLen - 1)) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void NTT(int len, int x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	register int *W, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W = w + i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		for(j = 0, k = 1; (1 << j) < len; ++j, k = (LL)k * inv2 % mod);
		std::reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
int tot, pr[maxn], d[maxn];
int n, inv[maxn], cnt, pp[maxe], ans;
LL m;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline int mod_inv(int x) {
	return x <= n ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	scanf("%d%lld", &n, &m);
	if(m % n > 0) {
		puts("0");
		return 0;
	}
	m /= n;
	initNTT(n << 1 | 1);
	inv[1] = d[1] = 1;
	for(int i = 2; i <= n; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int tmp = n; tmp > 1; ++cnt)
		for(pp[cnt] = d[tmp]; d[tmp] == pp[cnt]; tmp /= pp[cnt]);
	for(int msk = 0; msk < (1 << cnt); ++msk) {
		int sgn = 1, val = n, len, sum = 0;
		for(int i = 0; i < cnt; ++i)
			if((msk >> i) & 1) {
				sgn = -sgn;
				val /= pp[i];
			}
		for(len = 1; len < (val << 1 | 1); len <<= 1);
		A[0] = 1;
		B[0] = 0;
		for(int i = 1; i <= val; ++i) {
			A[i] = (LL)(mod - A[i - 1]) * (val + 2 - i) % mod * inv[i] % mod;
			B[i] = d[i] < i ? (LL)B[d[i]] * B[i / d[i]] % mod : mod_pow(i, val);
		}
		for(int i = val + 1; i < len; ++i)
			A[i] = B[i] = 0;
		NTT(len, A, 1);
		NTT(len, B, 1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len, A, -1);
		int pos = min(val - 1LL, m), rem = (m - pos) % mod, coeff = 1;
		if(rem + val - 1 >= mod) {
			pos -= mod - rem;
			rem = 0;
		} else if(rem > 0) {
			for(int i = 1; i < val; ++i)
				coeff = (LL)coeff * (rem + i) % mod * inv[i] % mod;
		}
		while(pos >= 0) {
			sum = (sum + (LL)coeff * A[pos + 1]) % mod;
			if(rem + val == mod) {
				pos -= mod - rem;
				rem = 0;
				coeff = 1;
			} else {
				coeff = (LL)coeff * (rem + val) % mod * mod_inv(rem + 1) % mod;
				--pos;
				mod_inc(rem, 1);
			}
		}
		mod_inc(ans, sgn < 0 ? mod - sum : sum);
	}
	ans = (LL)ans * inv[n] % mod;
	printf("%d\n", ans);
	return 0;
}
