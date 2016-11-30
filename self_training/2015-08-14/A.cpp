#include <cstdio>
#include <cstring>
const int maxn = 1010;
int n, p, q, a[maxn], f[maxn];
char s[maxn];
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	while(scanf("%d%d%d", &n, &p, &q) == 3)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%s", s);
			a[i] = a[i - 1] + strlen(s);
		}
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = i - 1; j >= 0; --j)
				if(a[i] - a[j] + (i - j - 1) > q)
					break;
				else
					upd(f[i], f[j] + 1);
		printf("%d\n", (f[n] - 1) / p + 1);
	}
	return 0;
}
