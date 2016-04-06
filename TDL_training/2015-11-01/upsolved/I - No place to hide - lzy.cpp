#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);

struct Seg{double l,r;}s[20009];;

int T,n;
double v[10009],x[10009],y[10009];
double d,t,a,R,l[20009],r[20009];
int ans,tmp;

int dcmp(double x)
{
	return (x>eps)-(x<-eps);
}
double sqr(double x)
{
	return x*x;
}
bool cmp(Seg a,Seg b)
{
	return dcmp(a.l-b.l)<0;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=0;i<=n;++i) scanf("%lf%lf%lf",v+i,x+i,y+i);
		for (int i=1;i<=n;++i)
		{
			x[i]-=x[0],y[i]-=y[0];
			if (v[0]<v[i])
			{
				puts("1");
				goto NEXT;
			}
			if (dcmp(x[i])==0 && dcmp(y[i])==0)
			{
				puts("1");
				goto NEXT;
			}
			d=sqrt(sqr(x[i])+sqr(y[i]));
			t=atan2(y[i],x[i]);
			a=sqrt(sqr(v[0])-sqr(v[i]))/v[0];
			s[i].l=t-acos(a);
			s[i].r=t+acos(a);
			//printf("%f %f %f\n",t,s[i].l,s[i].r);
		}
		sort(s+1,s+n+1,cmp);
		for (int i=1;i<=n;++i) l[i]=s[i].l,r[i]=s[i].r;
		ans=n+1;
		for (int i=1,j,k,p;i<=n;++i)
		{
			//printf("%f %f\n",l[i],r[i]);
			tmp=1;
			p=i;
			for (j=k=i+1;j<i+n;j=k)
			{
				R=r[p];
				if (R+eps>l[i]+2*pi) break;
				for (;k<i+n && l[k]<R+eps;++k) if (r[p]<r[k]) p=k;
				if (r[p]>R) ++tmp;
				else break;
			}
			R=r[p];
			if (R+eps>l[i]+2*pi) ans=min(ans,tmp);
			l[i+n]=l[i]+2*pi;
			r[i+n]=r[i]+2*pi;
		}
		printf("%d\n",ans==n+1?0:ans);
		NEXT:continue;
	}
	return 0;
}
