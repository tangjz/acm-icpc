#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 301, mod = (int)1e9 + 7;
int n, m, a[maxn], fact[maxn], f[2][maxn][maxn][maxn], ans;
int F(int i, int j, int k, int l) { // equal unread, less unread, greater unread, less read
	int &ret = f[i][j][k][l];
	if(ret != -1)
		return ret;
	if(!i && !j && !k)
		return ret = m - l;
	if(!i && j + k <= n - m && !l)
		return ret = (LL)(j + k + m) * fact[j + k] % mod;
	if(i + j + k <= n - m && l)
		--l;
	ret = 0;
	if(i)
		ret = (ret + (LL)i * F(i - 1, j, k, l)) % mod;
	if(j)
		ret = (ret + (LL)j * F(i, j - 1, k, l + 1)) % mod;
	if(k)
		ret = (ret + (LL)k * F(i, j, k - 1, l)) % mod;
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	fact[0] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		fact[i] = (LL)fact[i - 1] * i % mod;
	}
	std::sort(a + 1, a + n + 1);
	memset(f, -1, sizeof f);
	for(int i = 1; i <= n; ++i)
		ans = (ans + (LL)a[i] * F(1, i - 1, n - i, 0)) % mod;
	printf("%d\n", ans);
	return 0;
}
