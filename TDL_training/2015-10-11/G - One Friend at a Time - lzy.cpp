#include <cstdio>

using namespace std;

struct Node{int v;Node *x;}*e,*lnk[29],E[10009];
int f[2097152],c[29];
int T,n,m,k,u,v,ans;
int s;

void add(int u,int v)
{
    e->v=v;e->x=lnk[u],lnk[u]=e++;
}
void dps(int s)
{
    if (s>>n&1)
    {
        if (ans>f[s]) ans=f[s];
    }
    for (int i=2;i<=n;++i) if (!(s>>i&1) && c[i]>=k)
    {
        if (f[s]+1<f[s|1<<i])
        {
            f[s|1<<i]=f[s]+1;
            for (Node *p=lnk[i];p;p=p->x) ++c[p->v];
            dps(s|1<<i);
            for (Node *p=lnk[i];p;p=p->x) --c[p->v];
        }
    }
}
int main()
{
    scanf("%d",&T);
    for (int t=1;t<=T;++t)
    {
        scanf("%d%d%d",&n,&m,&k);
        for (int i=1;i<=n;++i) c[i]=0,lnk[i]=0;
        e=E;
        while (m--)
        {
            scanf("%d%d",&u,&v);
            add(u,v);
            add(v,u);
        }
        s=1;
        for (Node *p=lnk[1];p;p=p->x)
        {
            s|=1<<p->v;
            for (Node *q=lnk[p->v];q;q=q->x) ++c[q->v];
        }
        for (int i=0;i<1<<(n+1);++i) f[i]=0X3fffffff;
        f[s]=0;
        ans=0x3fffffff;
        dps(s);
        printf("Case #%d: ",t);
        if (ans<0x3fffffff)
        {
            if (ans) printf("%d\n",ans-1);
            else puts("0");
        }
        else puts("-1");
    }
    return 0;
}
