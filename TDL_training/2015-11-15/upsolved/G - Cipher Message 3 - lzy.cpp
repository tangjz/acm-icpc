#include <cstdio>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

typedef complex<double> Complex;

const double pi=acos(-1.0);

void change(Complex y[],int len)
{
	for (int i=1,j=len>>1;i<len-1;++i)
	{
		if (i<j) swap(y[i],y[j]);
		int k=len>>1;
		while (j>=k) j-=k,k>>=1;
		if (j<k) j+=k;
	}
}

void fft(Complex y[],int len,int on)
{
	change(y,len);
	for (int h=2;h<=len;h<<=1)
	{
		Complex w,u,t,wn(cos(-on*2*pi/h),sin(-on*2*pi/h));
		for (int j=0;j<len;j+=h)
		{
			w=Complex(1,0);
			for (int k=j;k<j+(h>>1);++k)
			{
				u=y[k];
				t=w*y[k+(h>>1)];
				y[k]=u+t;
				y[k+(h>>1)]=u-t;
				w=w*wn;
			}
		}
	}
	if (on==-1)
	{
		for (int i=0;i<len;++i) y[i]=Complex(y[i].real()/len,y[i].imag());
	}
}

#define N 250000

int n,m,l,sum;
int a[N+9],_a[N+9],b[N+9],_b[N+9];
Complex A[4*N+9],B[4*N+9];
int f[2*N+9],g[2*N+9];
int s[N+9],t[N+9];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;++i)
	{
		getchar();
		for (int j=7;j;--j) s[i]=s[i]*2+getchar()-'0';
		a[i]=getchar()-'0';
		_a[i]=!a[i];
	}
	for (int i=0;i<m;++i)
	{
		getchar();
		for (int j=7;j;--j) t[i]=t[i]*2+getchar()-'0';
		b[i]=getchar()-'0';
		_b[i]=!b[i];
	}
	reverse(b,b+m);
	reverse(_b,_b+m);

	sum=m+n-1;
	for (l=1;l<sum;l<<=1);
	for (int i=0;i<n;++i) A[i]=a[i];
	for (int i=n;i<l;++i) A[i]=0;
	for (int i=0;i<m;++i) B[i]=_b[i];
	for (int i=m;i<l;++i) B[i]=0;
	fft(A,l,+1);
	fft(B,l,+1);
	for (int i=0;i<l;++i) A[i]*=B[i];
	fft(A,l,-1);
	for (int i=0;i<sum;++i) g[i]+=A[i].real()+.5;
	//for (int i=0;i<sum;++i) printf("%d ",g[i]);puts("");

	for (int i=0;i<n;++i) A[i]=_a[i];
	for (int i=n;i<l;++i) A[i]=0;
	for (int i=0;i<m;++i) B[i]=b[i];
	for (int i=m;i<l;++i) B[i]=0;
	fft(A,l,+1);
	fft(B,l,+1);
	for (int i=0;i<l;++i) A[i]*=B[i];
	fft(A,l,-1);
	for (int i=0;i<sum;++i) g[i]+=A[i].real()+.5;
	//for (int i=0;i<sum;++i) printf("%d ",g[i]);puts("");

	for (int i=1,j=0;i<m;++i)
	{
		while (j && t[i]!=t[j]) j=f[j];
		f[i+1]=j=t[i]==t[j]?j+1:0;
	}

	int p=0,ans=0X7FFFFFFF;
	for (int i=0,j=0;i<n;++i)
	{
		while (j && s[i]!=t[j]) j=f[j];
		if (s[i]!=t[j]) j=0;
		else if (++j==m)
		{
			//printf("%d\n",i);
			if (ans>g[i])
			{
				ans=g[i];
				p=i;
				//printf("%d\n",ans);
			}
		}
	}
	if (ans<0X7FFFFFFF)
	{
		puts("Yes");
		printf("%d %d\n",ans,p-m+2);
	}
	else
	{
		puts("No");
	}
    return 0;
}
