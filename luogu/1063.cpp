#include <cstdio>
template<typename _> inline const _& max(const _& x, const _& y) { return y < x ? x : y; }
int n, energy[101], f[101][101], ans;
int main()
{
	int i, j, k, tmp;
	scanf("%d", &n);
	for(i = 0; i < n; ++i) scanf("%d", &energy[i]);
	for(tmp = 1; tmp < n; ++tmp)
		for(i = 0; i < n; ++i)
		{
			j = i + tmp;
			for(k = i; k < j; ++k) f[i][j % n] = max(f[i][j % n], f[i][k % n] + f[(k + 1) % n][j % n] + energy[i] * energy[(k + 1) % n] * energy[(j + 1) % n]);
		}
	for(i = 0; i < n; ++i) ans = max(ans, f[i][(i - 1 + n) % n]);
	printf("%d\n", ans);
}
