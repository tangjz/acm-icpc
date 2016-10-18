#include <stdio.h>
const int maxn = 100001, maxd = 1000001;
int t, n[2], a[2][maxn], sys_tim, tim[2][maxd], f[2][maxd];
inline void scan(int &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
int main()
{
	scan(t);
	while(t--)
	{
		++sys_tim;
		scan(n[0]), scan(n[1]);
		for(int o = 0; o < 2; ++o)
			for(int i = 1; i <= n[o]; ++i)
			{
				scan(a[o][i]);
				int v = tim[o][a[o][i] - 1] == sys_tim ? f[o][a[o][i] - 1] : 0;
				if(tim[o][a[o][i]] != sys_tim)
				{
					tim[o][a[o][i]] = sys_tim;
					f[o][a[o][i]] = v + 1;
				}
				else if(f[o][a[o][i]] < v + 1)
					f[o][a[o][i]] = v + 1;
			}
		int ans = 0;
		for(int i = 1; i <= n[0]; ++i)
		{
			if(tim[1][a[0][i]] != sys_tim)
				continue;
			int v = f[0][a[0][i]] < f[1][a[0][i]] ? f[0][a[0][i]] : f[1][a[0][i]];
			if(ans < v)
				ans = v;
		}
		printf("%d\n", ans);
	}
	return 0;
}
