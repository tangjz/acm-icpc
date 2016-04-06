#include <cstdio>

int n,m,d,c[10009];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&d);
		if (m<++c[d]) m=c[d];
	}
	printf("%d\n",m);
	return 0;
}
