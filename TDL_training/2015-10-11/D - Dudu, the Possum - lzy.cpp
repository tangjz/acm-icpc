#include <cstdio>

using namespace std;

int T,n,k,q;
double ans,x,c,s[609],w[609],p[19];

int main()
{
    scanf("%d",&T);
    for (int t=1;t<=T;++t)
    {
        scanf("%d%d",&n,&k);
        for (int j=1;j<=k;++j) scanf("%lf",p+j);
        for (int i=1;i<=n;++i)
        {
            scanf("%d",&q);
            w[i]=0.0;
            while (q--)
            {
                scanf("%lf%lf",&c,&x);
                w[i]+=c*x;
            }
        }
        s[1]=1.0;
        ans=w[1];
        for (int i=2;i<=n;++i)
        {
            s[i]=0.0;
            for (int j=1;j<=k&&j<i;++j)
            {
                s[i]+=s[i-j]*p[j];
            }
            ans+=s[i]*w[i];
        }
        printf("Case #%d: ",t);
        printf("%.6f\n",ans);
    }
    return 0;
}
