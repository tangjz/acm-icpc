#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 100
#define M 10000

struct Edge{int v;Edge *x;}*e,*lnk[N+9],E[2*M+9];

int T,n,m,ans,u,v;
bool g[N+9][N+9];
int l,r,q[N+9];
bool vis[N+9];

int tm,cnt,dn[N+9],lw[N+9],rt[N+9],z[N+9];
bool in[N+9];
int t,s[N+9];

void dfs(int u)
{
     dn[u]=lw[u]=++tm;
     in[u]=true;
     s[t++]=u;
     int w;
     for (Edge *p=lnk[u];p;p=p->x)
     if (!dn[w=p->v])
     {
        dfs(w);
        lw[u]=min(lw[u],lw[w]);
     }
     else if (in[w]) lw[u]=min(lw[u],dn[w]);
     if (dn[u]==lw[u])//栈中点构成一个强连通分量
     {
        z[++cnt]=0;
        do
        {
          w=s[--t];
          rt[w]=cnt;
          ++z[cnt];
          in[w]=false;
        } while (u!=w);
     }
}

int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		if (!(n || m)) break;
		e=E;
		for (int i=1;i<=n;++i) lnk[i]=0;
		while (m--)
		{
			scanf("%d%d",&u,&v);
			e->v=v,e->x=lnk[u],lnk[u]=e++;
		}
		memset(dn,0,sizeof dn);
		memset(lw,0,sizeof lw);
		tm=0;
		cnt=0;
		for (int i=1;i<=n;++i) if (!dn[i]) dfs(i);
		ans=0;
		for (int i=1;i<=cnt;++i) ans+=z[i]>1?z[i]:0;
		memset(g,0,sizeof g);
		for (int i=1;i<=n;++i) for (Edge *p=lnk[i];p;p=p->x)
		{
			if (rt[i]!=rt[p->v]) g[rt[i]][rt[p->v]]=true;
		}
		for (int i=1;i<=cnt;++i)
		{
			memset(vis,0,sizeof vis);
			r=0;
			q[r++]=i;
			for (l=0;l<r;++l)
			{
				u=q[l];
				for (v=1;v<=cnt;++v) if (g[u][v])
				{
					if (vis[v])
					{
						if (g[i][v])
						{
							g[i][v]=false;
						}
					}
					else
					{
						vis[q[r++]=v]=true;
					}
				}
			}
		}
		for (int i=1;i<=cnt;++i) for (int j=1;j<=cnt;++j) ans+=g[i][j];
		printf("Case %d: %d\n",++T,ans);
	}
	return 0;
}
