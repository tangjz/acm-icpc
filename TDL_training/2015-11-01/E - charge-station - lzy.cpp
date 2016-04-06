#include <cstdio>
#include <cmath>

#define N 139

int n,d,s[N][N],f[N];
int x[N],y[N];
bool g[N];


int sqr(int x)
{
    return x*x;
}
int find(int e)
{
    if (f[e]==e) return e;
    else return f[e]=find(f[e]);
}
void join(int a,int b)
{
    f[a]=b;
}
bool chk()
{
    for (int i=1;i<=n;++i) f[i]=i;
    for (int i=1;i<=n;++i) if (g[i])
    {
        for (int j=1;j<=n;++j) if (find(i)!=find(j))
        {

            if (g[j])
            {
                if (s[i][j]<=d) join(find(i),find(j));
            }
            else
            {
                if (2*s[i][j]<=d) join(find(i),find(j));
            }
        }
    }
    for (int i=1;i<=n;++i) if (find(i)!=find(1)) return false;
    return true;
}
int main()
{
    while (scanf("%d%d",&n,&d)==2)
    {
        for (int i=1;i<=n;++i) scanf("%d%d",x+i,y+i);
        for (int i=1;i<=n;++i) for (int j=1;j<=n;++j)
        {
            s[i][j]=ceil(sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])));
        }
        for (int x=n;x>=2;--x)
        {
            g[x]=false;
            for (int i=1;i<x;++i) g[i]=true;
            g[x]=!chk();
        }
        g[1]=true;
        if (!chk())
        {
            puts("-1");
            continue;
        }
        bool w=false;
        for (int i=n;i>=1;--i)
        {
            if (w) printf("%d",g[i]);
            else if (g[i])
            {
                w=g[i];
                printf("%d",g[i]);
            }
        }
        if (!w) printf("%d",0);
        putchar('\n');
    }
    return 0;
}
