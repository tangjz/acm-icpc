#include <cstdio>
#include <algorithm>

using std::min;

#define N 1000

typedef unsigned long long u64;

int n,m,u,v,s[N+9],c[N+9][N+9];
u64 x[N*N+9],y[N*N+9];
int l,r,q[10*N*N+9];
bool inq[N+9];

int main()
{
	while (scanf("%d%d%d%d%d%d",&n,&m,x,x+1,y,y+1)==6)
	{
		for (int k=2;k<n*n;++k)
		{
			x[k]=(12345+x[k-1]*23456+x[k-2]*34567+x[k-1]*x[k-2]*45678)%5837501;
			y[k]=(56789+y[k-1]*67890+y[k-2]*78901+y[k-1]*y[k-2]*89012)%9860381;
		}
		for (int i=0;i<n;++i) for (int j=0;j<n;++j) if (i!=j)
		{
			int k=i*n+j;
			c[i][j]=(x[k]*90123+y[k])%8475871+1;
		}
		int ans=m;
		const int inf=0x3FFFFFFF;
		for (int i=1;i<n;++i) s[i]=inf;
		r=0;
		inq[q[r++]=0]=true;
		for (l=0;l<r;++l)
		{
			inq[u=q[l]]=false;
			for (v=1;v<n;++v) if (s[v]>s[u]+c[u][v])
			{
				s[v]=s[u]+c[u][v];
				if (!inq[v])
				{
					inq[q[r++]=v]=true;
				}
			}
		}
		for (int i=1;i<n;++i) ans=min(ans,s[i]%m);
		printf("%d\n",ans);
	}
	return 0;
}
