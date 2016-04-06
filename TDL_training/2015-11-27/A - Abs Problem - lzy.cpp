#include <cstdio>
#include <cstdlib>

int n,s,t;

int main()
{
	while (scanf("%d",&n)==1)
	{
		s=t=0;
		for (int i=n-1;i>=1;--i) s=abs(s-i);
		s=abs(s-n);
		for (int i=n;i>=1;--i) t=abs(t-i);
		printf("%d %d\n",t,s);
		for (int i=n;i>=1;--i) printf("%d%c",i," \n"[i==1]);
		for (int i=n-1;i>=1;--i) printf("%d ",i);
		printf("%d\n",n);
	}
	return 0;
}
