#include <cstdio>
const int maxn = 200010;
typedef long long LL;
int n, ans;
LL a[maxn];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    for(int i = 1, last = 0, j; i <= n; i = j)
    {
        j = i + 1;
        while(a[last] > a[i] && j <= n)
        {
            a[i] += a[j++];
            ++ans;
        }
        if(a[last] > a[i])
        {
            a[last] += a[i];
            ++ans;
        }
        else
        	last = i;
    }
    printf("%d\n", ans);
    return 0;
}