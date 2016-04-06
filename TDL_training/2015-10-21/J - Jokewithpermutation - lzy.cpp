#include <cstdio>
#include <cstring>

int n,l,s[109],a[109];
int c[109];
char str[109];
bool u[109];

bool dfs(int k,int p)
{
    if (k==n+1) return true;
    if (p>=l) return false;
    int b=s[p];
    if (1<=b && b<=n && !u[b])
    {
        a[k]=b;
        u[b]=true;
        if (dfs(k+1,p+1)) return true;
        u[b]=false;
    }
    if (p+1<l)
    {
        b=10*s[p]+s[p+1];
        if (1<=b && b<=n && !u[b])
        {
            a[k]=b;
            u[b]=true;
            if (dfs(k+1,p+2)) return true;
            u[b]=false;
        }
    }
    return false;
}
int main()
{
    freopen("joke.in","r",stdin);
    freopen("joke.out","w",stdout);
    for (int i=1;i<=59;++i)
    {
        if (i<10) c[i]=c[i-1]+1;
        else c[i]=c[i-1]+2;
    }
    scanf("%s",str);
    l=strlen(str);
    for (int i=0;i<l;++i) s[i]=str[i]-'0';
    for (n=1;c[n]!=l;++n);
    dfs(1,0);
    for (int i=1;i<=n;++i) printf("%d ",a[i]);
    return 0;
}
