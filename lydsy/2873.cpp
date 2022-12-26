/*
 * 带标号边-仙人掌图
 * 具体看pty的题解
 */
#include <cstdio>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define LL long long
struct Program
{
	int n, pp;
	int c[208][208], s[208], f[208][208], ans;
	void Work()
	{
		scanf("%d%d", &n, &pp);
		rep(i,0,n) c[i][0] = 1;
		rep(i,1,n)
			rep(j,1,n)
			{
				c[i][j] = c[i-1][j-1] + c[i-1][j];
				if (c[i][j] >= pp) c[i][j] -= pp;
			}
		s[1] = 1; s[3] = 3;
		rep(i,4,n) s[i] = s[i-1] * i % pp;
		f[0][0] = 1;
		rep(i,1,n)
			rep(j,1,i)
				rep(t,1,i)
				{
					f[i][j] += (LL)c[i-1][t-1] * f[i-t][j-1] * s[t] % pp;
					if (f[i][j] >= pp) f[i][j] -= pp;
				}
		ans = 1;
		rep(i,3,n-1) {ans *= i; ans %= pp;}
		int tmp = 1;
		rep(i,2,n)
		{
			ans += (LL)f[n][i] * tmp % pp;
			if (ans >= pp) ans -= pp;
			tmp *= n; tmp %= pp;
		}
		printf("%d\n", ans);
	}
} program;
int main()
{
	program.Work();
}
