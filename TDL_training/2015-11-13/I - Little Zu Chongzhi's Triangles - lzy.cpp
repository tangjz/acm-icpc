#include <cstdio>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

int n,a[19];
bool u[19];

double calc(int a,int b,int c)
{
	double p=(a+b+c)/2.0;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}
int main()
{
	while (scanf("%d",&n),n)
	{
		for (int i=0;i<n;++i) scanf("%d",a+i);
		sort(a,a+n,greater<int>());
		for (int i=0;i<n;++i) u[i]=false;
		double s=0.0;
		for (int i=0;i<n;++i) for (int j=i+1;j<n;++j) for (int k=j+1;k<n;++k)
		{
			if (!u[i] && !u[j] && !u[k])
			{
				if (a[j]+a[k]>a[i])
				{
					u[i]=u[j]=u[k]=true;
					s+=calc(a[i],a[j],a[k]);
				}
			}
		}
		printf("%.2f\n",s);
	}
	return 0;
}
