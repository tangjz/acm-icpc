#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T,n,k;
int m[9];
int r[10009][9],g[10009][32];
int f[10009][9][32];

int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&k);
		memset(m,0,sizeof m);
		memset(g,0,sizeof g);
		for (int i=1;i<=n;++i)
		{
			for (int j=0;j<5;++j)
			{
				scanf("%d",r[i]+j);
				m[j]=max(m[j],r[i][j]);
				g[i][1<<j]=r[i][j];

			}
			for (int j=0;j<5;++j)
			{
				for (int s=0;s<32;++s) if (!(s&1<<j))
				{
					g[i][s|1<<j]+=g[i][s];
				}
			}
		}
		if (k>=5)
		{
			printf("%d\n",m[0]+m[1]+m[2]+m[3]+m[4]);
			continue;
		}
		memset(f[0],0,sizeof f[0]);
		for (int i=1;i<=n;++i)
		{
			memcpy(f[i],f[i-1],sizeof f[i]);
			for (int j=1;j<=k;++j)
			{
				for (int s=0;s<32;++s) for (int t=0;t<32;++t) if (!(s&t))
				{
					f[i][j][s|t]=max(f[i][j][s|t],f[i-1][j-1][s]+g[i][t]);
				}
			}
		}
		printf("%d\n",f[n][k][31]);
	}
	return 0;
}
