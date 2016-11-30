#include <stdio.h>
typedef long long LL;
const int maxn = 500001;
int n, m, f[maxn], s[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", f + i);
		f[i] ^= f[i - 1];
		s[i] = s[i - 1] + f[i];
	}
	while(m--)
	{
		int L, R, K;
		scanf("%d%d%d", &L, &R, &K);
		int len = R - L + 2, cnt = K ? len >> 1 : s[R + 1] - (L ? s[L - 1] : 0);
		printf("%lld\n", (LL)cnt * (len - cnt));
	}
	return 0;
}
