#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const int dx[]={0,+1,0,-1};
const int dy[]={+1,0,-1,0};

int n,m,x1[19],y1[19],x2[19],y2[19];
int g[19][19],c[19][19][19][19];
bool vis[19][19][19][19];
char map[19][19];
int l,r,p[309],q[309];
int f[65536][19];

void bfs(int u,int v)
{
	c[u][v][u][v]=0;
	r=0;
	p[r]=u,q[r]=v,++r;
	vis[u][v][u][v]=true;
	int x,y,_x,_y;
	for (l=0;l<r;++l)
	{
		x=p[l],y=q[l];
		for (int k=0;k<4;++k)
		{
			_x=x+dx[k],_y=y+dy[k];
			if (map[_x][_y]=='.' && !vis[u][v][_x][_y])
			{
				c[u][v][_x][_y]=c[u][v][x][y]+1;
				vis[u][v][_x][_y]=true;
				p[r]=_x,q[r]=_y,++r;
			}
		}
	}
}
int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		memset(map,0,sizeof map);
		for (int i=1;i<=n;++i) scanf("%s",map[i]+1);
		memset(vis,0,sizeof vis);
		memset(c,0x1F,sizeof c);
		for (int i=0;i<m;++i)
		{
			scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i);
			bfs(x2[i],y2[i]);
		}

		for (int i=0;i<m;++i) for (int j=0;j<m;++j)
		{
			g[i][j]=c[x2[i]][y2[i]][x1[j]][y1[j]];
		}
		memset(f,0x1F,sizeof f);
		for (int i=0;i<m;++i) f[1<<i][i]=0;
		for (int s=1;s<(1<<m);++s)
		{
			for (int i=0;i<m;++i) if (s&1<<i)
			{
				for (int j=0;j<m;++j) if (!(s&1<<j))
				{
					//printf("%d %d %d\n",s,i,j);
					f[s|1<<j][j]=min(f[s|1<<j][j],f[s][i]+g[i][j]);
				}
			}
		}
		int ans=6000000;
		for (int i=0;i<m;++i) ans=min(ans,f[(1<<m)-1][i]);
		if (ans<6000000) printf("%d\n",ans);
		else puts("-1");
	}
	return 0;
}
