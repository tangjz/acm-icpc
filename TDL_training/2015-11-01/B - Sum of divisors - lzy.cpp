#include <cstdio>

int n,m,b[109],p;
long long ans;

long long sqr(long long x)
{
    return x*x;
}
int main()
{
    while (scanf("%d%d",&n,&m)==2)
    {
        ans=0ll;
        for (int i=1,j;i*i<=n;++i) if (n%i==0)
        {
            for (int j=i;j;j/=m) ans+=sqr(j%m);
            if (i*i!=n) for (int j=n/i;j;j/=m) ans+=sqr(j%m);
        }
        p=0;
        do
        {
            b[p++]=ans%m;
        }
        while (ans/=m);
        while (p--) printf("%X",b[p]);
        putchar('\n');
    }
    return 0;
}
