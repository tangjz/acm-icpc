#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353, maxLen = 17, maxs = 1 << maxLen | 1, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs], inv[maxs], A[maxs], B[maxs], C[maxs];
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
	inv[1] = 1;
	for(int i = 2; i < (1 << bitLen); ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
}
void NTT(int len, int x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			swap(x[i], x[j]);
	}
	register int *W = w + 1, t;
	for(i = 1; i < len; W += i, i <<= 1)
		for(j = 0; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		for(j = 0, k = 1; (1 << j) < len; ++j, k = (LL)k * inv2 % mod);
		reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
void polyExp(int n, int cur[], int nxt[]) {
	static int f[maxs], g[maxs], h[maxs];
	for(int i = 1; i < n; ++i)
		f[i - 1] = (LL)cur[i] * i % mod;
	f[n - 1] = 0;
	g[0] = h[0] = B[0] = 1;
	NTT(1, B, 1);
	for(int len = 1; len < n; len <<= 1) {
		memcpy(C, h, len * sizeof(int));
		NTT(len, C, 1);
		for(int i = 0; i < len; ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len, B, -1);
		B[0] = mod_sub(B[0], 1);
		for(int i = 1; i < len; ++i)
			A[i - 1] = (LL)g[i] * i % mod;
		A[len - 1] = 0;
		NTT(len, A, 1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len, A, -1);
		for(int i = len - 3; i >= 0; --i)
			A[i + 1] = mod_sub(A[i], f[i]);
		A[0] = A[len - 1];
		A[len - 1] = 0;
		for(int i = 0, j = len - 1; i < len && j + 1 < n; ++i, ++j)
			A[i] = mod_sub(A[i], f[j]);
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		memcpy(C, f, (len - 1) * sizeof(int));
		memset(C + len - 1, 0, (len + 1) * sizeof(int));
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			B[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, B, -1);
		for(int i = 0; i < len; ++i)
			A[i] = (LL)mod_sub(A[i], i ? B[i - 1] : 0) * inv[len + i] % mod;
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		memcpy(B, g, len * sizeof(int));
		memset(B + len, 0, len * sizeof(int));
		NTT(len << 1, B, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * B[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			g[len + i] = mod_sub(0, A[i]);
		if((len << 1) >= n)
			break;
		memcpy(B, g, (len << 1) * sizeof(int));
		NTT(len << 1, B, 1);
		memcpy(C, h, len * sizeof(int));
		memset(C + len, 0, len * sizeof(int));
		NTT(len << 1, C, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)B[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		memcpy(A, A + len, len * sizeof(int));
		memset(A + len, 0, len * sizeof(int));
		NTT(len << 1, A, 1);
		for(int i = 0; i < (len << 1); ++i)
			A[i] = (LL)A[i] * C[i] % mod;
		NTT(len << 1, A, -1);
		for(int i = 0; i < len; ++i)
			h[len + i] = mod_sub(0, A[i]);
	}
	memcpy(nxt, g, n * sizeof(int));
}
int n, y, op, mul, ans;
vector<int> e[maxn];
pair<int, int> dfs(int u, int par) {
	pair<int, int> ret = make_pair(1, mul);
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == par)
			continue;
		pair<int, int> tmp = dfs(v, u);
		int sum = mod_add(tmp.first, tmp.second);
		ret.second = ((LL)ret.first * tmp.second + (LL)ret.second * sum) % mod;
		ret.first = (LL)ret.first * sum % mod;
	}
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &y, &op);
	if(y == 1) {
		printf("%d\n", mod_pow(n, op * (n - 2)));
		return 0;
	}
	if(!op) {
		set<pair<int, int> > Hash;
		for(int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			Hash.insert(u > v ? make_pair(v, u) : make_pair(u, v));
		}
		int cnt = 0;
		for(int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			cnt += Hash.count(u > v ? make_pair(v, u) : make_pair(u, v));
		}
		printf("%d\n", mod_pow(y, n - cnt));
		return 0;
	}
	mul = (LL)mod_pow(n, op) * y % mod * mod_pow(mod + 1 - y, mod - 2) % mod;
	if(op == 1) {
		for(int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		ans = dfs(1, -1).second;
	} else {
		static int f[maxn];
		initNTT(n + 1);
		f[0] = 0;
		for(int i = 1, prd = mul; i <= n; ++i) {
			prd = (LL)prd * inv[i] % mod;
			f[i] = (LL)prd * mod_pow(i, i) % mod;
		}
		polyExp(n + 1, f, f);
		ans = f[n];
		for(int i = 2; i <= n; ++i)
			ans = (LL)ans * i % mod;
	}
	ans = (LL)ans * mod_pow(n, mod - 1 - (op << 1)) % mod * mod_pow(mod + 1 - y, n) % mod;
	printf("%d\n", ans);
	return 0;
}