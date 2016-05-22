#include <stdio.h>
#include <cstring>
const int maxn = 100002, mod = 9973;
int inv[mod], n, m, h[maxn];
char str[maxn];
int main()
{
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	while(scanf("%d%s", &m, str + 1) == 2)
	{
		n = strlen(str + 1);
		h[0] = 1;
		for(int i = 1; i <= n; ++i)
			h[i] = h[i - 1] * (str[i] - 28) % mod;
		while(m--)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", h[r] * inv[h[l - 1]] % mod);
		}
	}
	return 0;
}
