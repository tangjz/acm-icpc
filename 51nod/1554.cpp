#include <stdio.h>
const int maxn = 1000001;
int n, m, f[maxn];
char s[maxn];
int main()
{
	scanf("%d%d%s", &n, &m, s);
	for(int i = 1, j = 0; i < n; ++i)
	{
		for( ; j && s[i] != s[j]; j = f[j]);
		f[i + 1] = s[i] == s[j] ? ++j : 0;
	}
	for(int i = 1; i <= n; ++i)
	{
		int ctr = i / (i - f[i]), rem = i % (i - f[i]);
		s[i - 1] = "01"[ctr % m + (rem > 0) <= ctr / m];
	}
	puts(s);
	return 0;
}
