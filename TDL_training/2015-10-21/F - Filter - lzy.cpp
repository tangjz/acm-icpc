#include <cstdio>
#include <bitset>

using namespace std;

int m,f,n,q,t,a[109],u;
bitset<1009> b[1009],c;
bool y[1009];
int ans;

int main()
{
    freopen("filter.in","r",stdin);
    freopen("filter.out","w",stdout);
    scanf("%d%d",&m,&f);
    for (int i=0;i<f;++i)
    {
        scanf("%d",a+i);
        a[i]%=m;
    }
    scanf("%d",&n);
    for (int i=0;i<n;++i)
    {
        for (int j=0;j<(m+3)/4;++j)
        {
            scanf("%1x",&t);
            for (int k=0;k<4;++k) if (t>>k&1) b[i].set(4*j+k);
        }
    }
    scanf("%d",&q);
    for (int i=0;i<q;++i)
    {
        scanf("%d",&u);
        u%=m;
        c.reset();
        for (int j=0;j<f;++j) c.set(u*a[j]%m);
        for (int j=0;j<n;++j) if (!y[j]) ans+=y[j]=(b[j]&c)==c;
    }
    printf("%d",ans);
    for (int i=0;i<n;++i) if (y[i]) printf(" %d",i);
    return 0;
}
