#include <cstdio>
#include <cstring>

const int mod=1000000007;
const int god=22222223;

int n;
int f[100009][2][3],g[100009][2][3];
char s[100009],t[100009];

inline void upd(int i,bool x,bool y)
{
	for (int j=0;j<=1;++j)
	{
		if ((j^x)<y)
		{
			f[i][j^x][2]+=f[i-1][j][2];
			if (f[i][j^x][2]>=mod) f[i][j^x][2]-=mod;
			f[i][j^x][2]+=f[i-1][j][1];
			if (f[i][j^x][2]>=mod) f[i][j^x][2]-=mod;
			g[i][j^x][2]+=g[i-1][j][2];
			if (g[i][j^x][2]>=god) g[i][j^x][2]-=god;
			g[i][j^x][2]+=g[i-1][j][1];
			if (g[i][j^x][2]>=god) g[i][j^x][2]-=god;
		}
		else if ((j^x)>y)
		{
			f[i][j^x][1]+=f[i-1][j][0];
			if (f[i][j^x][1]>=mod) f[i][j^x][1]-=mod;
			g[i][j^x][1]+=g[i-1][j][0];
			if (g[i][j^x][1]>=god) g[i][j^x][1]-=god;

		}
		else
		{
			f[i][j^x][0]+=f[i-1][j][0];
			if (f[i][j^x][0]>=mod) f[i][j^x][0]-=mod;
			g[i][j^x][0]+=g[i-1][j][0];
			if (g[i][j^x][0]>=god) g[i][j^x][0]-=god;
		}
	}
}

bool con(int i,int j,int k);

bool dpu(int i,bool x,bool y,int _j,int k)
{
	int j=_j^x;
	{
		if (_j<y && k==2)
		{
			if (f[i-1][j][2] || g[i-1][j][2])
			{
				s[i]=x^'0';
				t[i]=y^'1';
				if (con(i-1,j,2)) return true;
			}
			if (f[i-1][j][1] || g[i-1][j][1])
			{
				s[i]=x^'0';
				t[i]=y^'1';
				if (con(i-1,j,1)) return true;
			}
		}
		else if (_j>y && k==1)
		{
			if (f[i-1][j][0] || g[i-1][j][0])
			{
				s[i]=x^'0';
				t[i]=y^'1';
				if (con(i-1,j,0)) return true;
			}
		}
		else if (_j==y && k==0)
		{
			if (f[i-1][j][0] || g[i-1][j][0])
			{
				s[i]=x^'0';
				t[i]=y^'1';
				if (con(i-1,j,0)) return true;
			}
		}
	}
	return false;
}
bool con(int i,int j,int k)
{
	if (i==0) return true;
	if (s[i]=='?')
	{
		if (t[i]=='?')
		{
			for (int x=0;x<=1;++x) for (int y=0;y<=1;++y)
			{
				if (dpu(i,x,y,j,k)) return true;
			}
		}
		else
		{
			for (int x=0;x<=1;++x) if (dpu(i,x,t[i]^'1',j,k)) return true;
		}
	}
	else
	{
		int x=s[i]^'0';
		if (t[i]=='?')
		{
			for (int y=0;y<=1;++y) if (dpu(i,x,y,j,k)) return true;
		}
		else
		{
			if (dpu(i,x,t[i]^'1',j,k)) return true;
		}
	}
	return false;
}
int main()
{
	while (scanf("%s%s",s+1,t+1)==2)
	{
		n=strlen(s+1);
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		f[0][0][0]=1;
		g[0][0][0]=1;
		for (int i=1;i<=n;++i)
		{
			if (s[i]=='?')
			{
				if (t[i]=='?')
				{
					for (int x=0;x<=1;++x) for (int y=0;y<=1;++y) upd(i,x,y);
				}
				else
				{
					for (int x=0;x<=1;++x) upd(i,x,t[i]^'1');
				}
			}
			else
			{
				int x=s[i]^'0';
				if (t[i]=='?')
				{
					for (int y=0;y<=1;++y) upd(i,x,y);
				}
				else
				{
					upd(i,x,t[i]^'1');
				}
			}
		}
		int anf=0,ang=0;
		bool flag=true;
		for (int i=1;i<=n;++i) if (s[i]=='1' || t[i]=='1') flag=false;
		if (flag) ++anf,++ang;
		for (int j=0;j<=1;++j) for (int k=1;k<=2;++k)
		{
			if ((anf+=f[n][j][k])>=mod) anf-=mod;
			if ((ang+=g[n][j][k])>=god) ang-=god;
		}
		if (anf==0 && ang==0)
		{
			puts("IMPOSSIBLE");
		}
		else if (anf==1 && ang==1)
		{
			puts("UNIQUE");
			if (flag)
			{
				for (int i=1;i<=n;++i) putchar('0');puts("");
				for (int i=1;i<=n;++i) putchar('0');puts("");
			}
			else
			{
				for (int j=0;j<=1;++j) for (int k=1;k<=2;++k) if (f[n][j][k] || g[n][j][k]) con(n,j,k);
				puts(s+1);
				puts(t+1);
			}
		}
		else
		{
			printf("AMBIGUOUS %d\n",anf);
		}
	}
	return 0;
}
