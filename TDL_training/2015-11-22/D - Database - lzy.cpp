#include <cstdio>
#include <utility>
#include <map>

using std::map;
using std::pair;

typedef unsigned u32;
typedef unsigned long long u64;

typedef pair<u64,u64> hash;

const u32 k1=100000009u;
const u32 k2=1000000007u;

int n,m,c,r1,r2,c1,c2;
u64 a,b;
hash h[10009][19];
map<pair<hash,hash>,int> f;

int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		getchar();
		for (int i=0;i<n;++i)
		{
			m=0;
			for (;;)
			{
				a=0,b=0;
				for (;;)
				{
					c=getchar();
					if (c==',' || c=='\n') break;
					a=a*k1+c;
					b=b*k2+c;
				}
				h[i][m].first=a;
				h[i][m].second=b;
				++m;
				if (c=='\n') break;
			}
		}
		for (int i=0;i<m;++i) for (int j=i+1;j<m;++j)
		{
			f.clear();
			for (int k=0;k<n;++k)
			{
				if (f.count(make_pair(h[k][i],h[k][j])))
				{
					r1=f[make_pair(h[k][i],h[k][j])];
					r2=k;
					c1=i;
					c2=j;
					goto NO;
				}
				f[make_pair(h[k][i],h[k][j])]=k;
			}
		}
		puts("YES");
		continue;
		NO:puts("NO");
		printf("%d %d\n",r1+1,r2+1);
		printf("%d %d\n",c1+1,c2+1);
	}
	return 0;
}
