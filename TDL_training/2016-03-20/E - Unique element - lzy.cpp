#include <cstdio>

int n,a,b,c,d,e;

int main()
{
	scanf("%d",&n);
	int l=1,r=n,m;
	while (l+2<r) {
		m=(l+r)/2;
		printf("? %d\n",m);
		fflush(stdout);
		scanf("%d",&a);
		printf("? %d\n",m+1);
		fflush(stdout);
		scanf("%d",&b);
		if (m&1) {
			if (a==b) l=m+2;
			else r=m+1;
		}
		else {
			if (a==b) r=m-1;
			else l=m;
		}
	}
	if (l==r) {
		printf("? %d\n",l);
		fflush(stdout);
		scanf("%d",&a);
		printf("! %d\n",a);
	} else if (l+1==r) {
		printf("? %d\n",l);
		fflush(stdout);
		scanf("%d",&a);
		printf("? %d\n",r);
		fflush(stdout);
		scanf("%d",&b);
		printf("? %d\n",l&1?r+1:l-1);
		fflush(stdout);
		scanf("%d",&c);
		printf("! %d\n",a^b^c);
	} else {
		if (l&1) {
			printf("? %d\n",l);
			fflush(stdout);
			scanf("%d",&a);
			printf("? %d\n",r);
			fflush(stdout);
			scanf("%d",&b);
			printf("? %d\n",l+1);
			fflush(stdout);
			scanf("%d",&c);
			printf("! %d\n",a^b^c);
		} else {
			printf("? %d\n",l);
			fflush(stdout);
			scanf("%d",&a);
			printf("? %d\n",r);
			fflush(stdout);
			scanf("%d",&b);
			printf("? %d\n",l+1);
			fflush(stdout);
			scanf("%d",&c);
			printf("? %d\n",l-1);
			fflush(stdout);
			scanf("%d",&d);
			printf("? %d\n",r+1);
			fflush(stdout);
			scanf("%d",&e);
			printf("! %d\n",a^b^c^d^e);
		}
	}
	return 0;
}
