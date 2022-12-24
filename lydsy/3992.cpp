#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxLen = 14, maxs = 1 << maxLen | 1, mod = 1004535809, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs << 1 | 1];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
int mod_pow(int x, int k, int m) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % m)
		if(k & 1)
			ret = (LL)ret * x % m;
	return ret;
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << bitLen);
	W[0] = 1;
	W[1] = mod_pow(gen, (mod - 1) >> bitLen, mod);
	for(int i = 2; i < (1 << bitLen); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << bitLen) - 1; i > 0; --i)
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
	register int *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
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
int primitiveRoot(int m) {
	int cnt = 0, pr[5];
	for(int i = 2, tmp = m - 1; i <= tmp; ++i) {
		if(i * i > tmp)
			i = tmp;
		if(tmp % i == 0)
			for(pr[cnt++] = i; tmp % i == 0; tmp /= i);
	}
	for(int gen = 2; gen < m; ++gen) {
		bool flag = mod_pow(gen, m - 1, m) == 1;
		for(int i = 0; i < cnt && flag; ++i)
			flag &= mod_pow(gen, (m - 1) / pr[i], m) != 1;
		if(flag)
			return gen;
	}
	return 1;
}
int n, m, rt, q, t, x, idx[maxs], f[maxs], g[maxs];
int main() {
	scanf("%d%d%d%d", &n, &m, &x, &t);
	int len;
	for(len = 1; len < ((m - 2) << 1 | 1); len <<= 1);
	initNTT(len);
	rt = primitiveRoot(m);
	for(int i = 0, u = 1; i < m - 1; ++i, u = (LL)u * rt % m)
		idx[u] = i;
	q = idx[x];
	while(t--) {
		scanf("%d", &x);
		if(!x)
			continue;
		++f[idx[x]];
	}
	g[0] = 1;
	NTT(len, f, 1);
	while(1) {
		if(n & 1) {
			NTT(len, g, 1);
			for(int i = 0; i < len; ++i)
				g[i] = (LL)f[i] * g[i] % mod;
			NTT(len, g, -1);
			for(int i = len - 1; i >= m - 1; --i)
				if(g[i]) {
					g[i - m + 1] = mod_add(g[i - m + 1], g[i]);
					g[i] = 0;
				}
		}
		if(!(n >>= 1))
			break;
		for(int i = 0; i < len; ++i)
			f[i] = (LL)f[i] * f[i] % mod;
		NTT(len, f, -1);
		for(int i = len - 1; i >= m - 1; --i)
			if(f[i]) {
				f[i - m + 1] = mod_add(f[i - m + 1], f[i]);
				f[i] = 0;
			}
		NTT(len, f, 1);
	}
	printf("%d\n", g[q]);
	return 0;
}
