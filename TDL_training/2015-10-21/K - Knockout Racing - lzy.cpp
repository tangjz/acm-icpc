#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,x,y,d,k,t,a[1009],b[1009],c[1009];

int main()
{
    freopen("knockout.in","r",stdin);
    freopen("knockout.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i)
    {
        scanf("%d%d",a+i,b+i);
        if (a[i]>b[i]) swap(a[i],b[i]);
        c[i]=b[i]-a[i];
    }
    while (m--)
    {
        scanf("%d%d%d",&x,&y,&t);
        int ans=0;
        for (int i=0;i<n;++i)
        {
            d=t%(2*c[i]);
            if (d<=c[i]) k=a[i]+d;
            else k=b[i]-(d-c[i]);
            if (x<=k && k<=y) ++ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}
