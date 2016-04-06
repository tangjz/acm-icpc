#include <cstdio>
#include <cstring>
int n, cnt;
char str[21];
bool r[21], c[21], u[41], d[41], ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = 1;
		cnt = 0;
		memset(r, 0, sizeof r);
		memset(c, 0, sizeof c);
		memset(u, 0, sizeof u);
		memset(d, 0, sizeof d);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < n; ++j)
				if(str[j] == '1')
				{
					++cnt;
					r[i] ? ans = 0 : r[i] = 1;
					c[j] ? ans = 0 : c[j] = 1;
					u[i + j] ? ans = 0 : u[i + j] = 1;
					d[i - j + 19] ? ans = 0 : d[i - j + 19] = 1;
				}
		}
		ans &= cnt == n;
		puts(ans ? "Move Forward!" : "Bad End!");
	}
	return 0;
}
