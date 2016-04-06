#include <cstring>
#include <cstdio>
#include <algorithm>

int n,m,l,x[19];
char a[19],b[19],s[19];
double p,q;
bool flag;

int main()
{
	scanf("%s%s",a,b);
	n=strlen(a);
	p=1.0;
	for (int i=0;i<n;++i)
	{
		scanf("%s",s);
		std::swap(s[3],s[4]);
		if (a[i]==b[i]) continue;
		m=0;
		q=0.0;
		for (int j=0;j<6;++j) if (s[j]==a[i])
		{
			++m;
			l=0;
			flag=false;
			for (int k=0;k<6;++k) if (s[k]==b[i])
			{
				x[l++]=k;
			}
			if (l==0) continue;
			for (int k=0;k<l;++k)
			{
				if (x[k]+j==5)
				{
					flag=true;
					goto OK;
				}
				else
				{
					for (int y=0;y<l;++y) if (y!=k)
					{
						if (x[y]+x[k]!=5)
						{
							flag=true;
							goto OK;
						}
					}
				}
			}
			OK:
			q+=flag?1.0:0.5;
		}
		p*=q/m;
	}
	printf("%.8f\n",p);
	return 0;
}
