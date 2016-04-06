#include <cstdio>

int p,q;
int n,a[233];

int main()
{
	freopen("reversed-fraction.in","r",stdin);
	freopen("reversed-fraction.out","w",stdout);
	scanf("%d%d",&p,&q);
	for (int o;p;o=q%p,q=p,p=o)
		a[++n]=q/p;
	p=0,q=1;
	for (int i=1;i<=n;++i)
	{
		int o=a[i]*q+p;
		p=q;
		q=o;
	}
	printf("%d %d\n",p,q);
	return 0;
}
