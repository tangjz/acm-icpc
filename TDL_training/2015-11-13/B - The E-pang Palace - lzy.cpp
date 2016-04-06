#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

int n,x,y,l,ll,rr,r,s1,s2,ans;
bool u[209],v[209],g[209][209];
int p,q,s[209],t[209];

int main()
{
	while (scanf("%d",&n),n)
	{
		memset(u,0,sizeof u);
		memset(v,0,sizeof v);
		memset(g,0,sizeof g);

		for (int i=0;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			u[x]=true;
			v[y]=true;
			g[x][y]=true;
		}
		p=0;
		for (int i=0;i<=200;++i) if (u[i]) s[p++]=i;
		q=0;
		for (int j=0;j<=200;++j) if (v[j]) t[q++]=j;
		ans=0;
		for (int o=1;o+2<p;++o)
		{
			s1=0;
			for (int i=0;i<o;++i) for (int j=i+1;j<=o;++j)
			{
				l=r=0;
				for (int k=0;k<q;++k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					l=t[k];
					break;
				}
				for (int k=q-1;k>=0;--k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					r=t[k];
					break;
				}
				s1=max(s1,(r-l)*(s[j]-s[i]));
			}
			s2=0;
			for (int i=o+1;i<p;++i) for (int j=i+1;j<p;++j)
			{
				l=r=0;
				for (int k=0;k<q;++k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					l=t[k];
					break;
				}
				for (int k=q-1;k>=0;--k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					r=t[k];
					break;
				}
				s2=max(s2,(r-l)*(s[j]-s[i]));
			}
			if (s1 && s2) ans=max(ans,s1+s2);
		}
		//------------------------------------------
		for (int o=1;o+2<q;++o)
		{
			s1=0;
			for (int i=0;i<o;++i) for (int j=i+1;j<=o;++j)
			{
				l=r=0;
				for (int k=0;k<p;++k) if (g[s[k]][t[i]] && g[s[k]][t[j]])
				{
					l=s[k];
					break;
				}
				for (int k=p-1;k>=0;--k) if (g[s[k]][t[i]] && g[s[k]][t[j]])
				{
					r=s[k];
					break;
				}
				s1=max(s1,(r-l)*(t[j]-t[i]));
			}
			s2=0;
			for (int i=o+1;i<q;++i) for (int j=i+1;j<q;++j)
			{
				l=r=0;
				for (int k=0;k<p;++k) if (g[s[k]][t[i]] && g[s[k]][t[j]])
				{
					l=s[k];
					break;
				}
				for (int k=p-1;k>=0;--k) if (g[s[k]][t[i]] && g[s[k]][t[j]])
				{
					r=s[k];
					break;
				}
				s2=max(s2,(r-l)*(t[j]-t[i]));
			}
			if (s1 && s2) ans=max(ans,s1+s2);
		}
		for (int i=0;i<p;++i) for (int ii=i+1;ii<p;++ii)
		{
			for (int jj=ii+1;jj<p;++jj) for (int j=jj+1;j<p;++j)
			{
				l=r=0;
				for (int k=0;k<q;++k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					l=k;
					break;
				}
				for (int k=q-1;k>=0;--k) if (g[s[i]][t[k]] && g[s[j]][t[k]])
				{
					r=k;
					break;
				}
				s1=(s[j]-s[i])*(t[r]-t[l]);
				ll=rr=0;
				for (int k=l+1;k<r;++k) if (g[s[ii]][t[k]] && g[s[jj]][t[k]])
				{
					ll=k;
					break;
				}
				for (int k=r-1;k>l;--k) if (g[s[ii]][t[k]] && g[s[jj]][t[k]])
				{
					rr=k;
					break;
				}
				s2=(s[jj]-s[ii])*(t[rr]-t[ll]);
				if (s1 && s2) ans=max(ans,s1);
			}
		}
		if (ans) printf("%d\n",ans);
		else puts("imp");
	}
	return 0;
}
