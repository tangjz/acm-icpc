#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min;

#define N 100

const int inf=0X1FFFFFFF;
const int lmt=65536;

int n,m,a,s,t,S,T,u,v,sum,f0,f1;
int b[N+9][N+9],c[N+9][N+9],f[N+9][N+9];
int l,r,p[N+9],q[N+9];
int stk[N+9],ptr;

void dfs(int u,int f)
{
	if (u==t)
	{
		for (int i=1;i<ptr;++i) printf("%d ",stk[i]);
		putchar('\n');
	}
	else
	{
		int g;
		for (int i=1;i<=n&&f;++i) if (b[u][i])
		{
			g=min(f,b[u][i]);
			stk[ptr++]=u;
			dfs(i,g);
			b[u][i]-=g;
			f-=g;
			--ptr;
		}
	}
}
bool bfs(int src,int snk)
{
	if (src==snk) return true;
	memset(p,0,sizeof p);
	r=0;
	q[r++]=src;
	for (l=0;l<r;++l)
	{
		u=q[l];
		for (v=1;v<=n;++v) if (!p[v])
		{
			if (f[u][v]<c[u][v]) p[q[r++]=v]=u;
			if (f[v][u]) p[q[r++]=v]=-u;
		}
		if (p[snk]) return true;
	}
	return false;
}
int main()
{
	while (scanf("%d",&n)==1)
	{
		memset(b,0,sizeof b);
		memset(c,0,sizeof c);
		memset(f,0,sizeof f);
		s=n+1,t=n+2;
		S=n+3,T=n+4;
		c[S][s]=inf,c[t][T]=inf;
		sum=0;
		for (int i=1,j;i<=n;++i)
		{
			c[s][i]=c[i][t]=lmt;
			scanf("%d",&a);
			while (a--)
			{
				scanf("%d",&j);
				++sum;
				++b[i][j];
				c[i][j]=lmt;
				++c[S][j],++c[i][T];
			}
		}
		n+=4;
		for (f0=0;bfs(S,T);f0+=a)
		{
			a=inf;
			for (int i=T;i!=S;i=abs(p[i]))
			{
				if (p[i]<0) a=min(a,f[i][-p[i]]);
				else a=min(a,c[p[i]][i]-f[p[i]][i]);
			}
			for (int i=T;i!=S;i=abs(p[i]))
			{
				if (p[i]<0) f[i][-p[i]]-=a;
				else f[p[i]][i]+=a;
			}
		}
		f0-=sum;
		memset(c,0,sizeof c);
		n-=2;
		for (int i=1;i<=n;++i) for (int j=1;j<=n;++j)
		{
			b[i][j]+=f[i][j];
			c[i][j]=f[j][i];
		}
		memset(f,0,sizeof f);
		for (f1=0;bfs(t,s);f1+=a)
		{
			a=inf;
			for (int i=s;i!=t;i=abs(p[i]))
			{
				if (p[i]<0) a=min(a,f[i][-p[i]]);
				else a=min(a,c[p[i]][i]-f[p[i]][i]);
			}
			for (int i=s;i!=t;i=abs(p[i]))
			{
				if (p[i]<0) f[i][-p[i]]-=a;
				else f[p[i]][i]+=a;
			}
		}
		printf("%d\n",f0-f1);
		for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) b[i][j]-=f[j][i];
		dfs(s,f0-f1);
	}
	return 0;
}
