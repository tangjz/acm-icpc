#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define N 500

const double eps=1e-6;
const double pi=acos(-1.0);

int n,o[N+9];
double L,R,U,V,dis[N+9],the[N+9],det;
double x[N+9],y[N+9],rad[N+9],l[N+9],r[N+9];

int dcmp(double x)
{
	return (x>eps) - (x<eps);
}
double sqr(double x)
{
	return x*x;
}
bool cmp(int a,int b)
{
	if (dcmp(l[a]-l[b])==0) return dcmp(r[a]-r[b])<0;
	else return dcmp(l[a]-l[b])<0;
}

double calc(double a)
{
	double d,ret=0.0;
	for (int _k=0,k;_k<n+n;++_k)
	{
		k=o[_k];
		if (dcmp(l[k]-a)<0 && dcmp(a-r[k])<0)
		{
			d=dis[k]*sin(abs(the[k]-a));
			ret+=2.0*sqrt(sqr(rad[k])-sqr(d));
		}
	}
	return ret;
}
int main()
{
	while (scanf("%d",&n)==1)
	{
		for (int i=0;i<n;++i)
		{
			o[i]=i;
			scanf("%lf%lf%lf",x+i,y+i,rad+i);
			dis[i]=sqrt(sqr(x[i])+sqr(y[i]));
			the[i]=atan2(y[i],x[i]);
			det=asin(rad[i]/dis[i]);
			l[i]=the[i]-det,r[i]=the[i]+det;
		}
		for (int i=0;i<n;++i)
		{
			o[i+n]=i+n;
			dis[i+n]=dis[i];
			the[i+n]=the[i]+2*pi;
			rad[i+n]=rad[i];
			l[i+n]=l[i]+2*pi;
			r[i+n]=r[i]+2*pi;
			x[i+n]=x[i];
			y[i+n]=y[i];
		}
		sort(o,o+n+n,cmp);
		double ans=0.0;
		for (int _i=0,_j,i,j;_i<n;++_i)
		{
			i=o[_i];
			L=l[i],R=r[i];
			for (_j=_i;_j<_i+n;++_j)
			{
				j=o[_j];
				if (dcmp(l[j]-r[i])<=0)
				{
					L=max(l[i],l[j]);
					R=min(r[i],r[j]);
					int cnt=60;
					while (cnt--)
					{
						U=L+(R-L)/3;
						V=R-(R-L)/3;
						if (calc(U)<calc(V)) L=U;
						else R=V;
					}
					ans=max(ans,calc(L));
				}
				else break;
			}
			//printf("%d %d %f %f\n",_i,_j,L,R);


			//printf("%.8f\n",ans);
		}
		printf("%.10f\n",ans);
	}
	return 0;
}
