#include <cstdio>
const int maxn = 200001;
int n, a[maxn], b[maxn], c[maxn], s[maxn], tag[maxn];
double ans;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for(int i = 1; i <= n; ++i)
        scanf("%d", b + i);
    for(int i = 1; i <= n; ++i)
        c[b[i]] = i;
    for(int i = 1; i <= n; ++i)
        a[i] = c[a[i]];
    for(int i = 1; i <= n; ++i)
        b[a[i]] = i;
    a[n + 1] = b[n + 1] = 0;
    s[1] = 1;
    ++tag[1];
    --tag[2];
    for(int i = 2; i <= n; ++i)
    {
        if(b[i] > b[i + 1])
        {
            s[i] = 1;
            ++tag[i];
            --tag[i + 1];
        }
        s[i] += s[i - 1];
    }
    for(int i = 1; i <= n; ++i)
        if(s[a[i] - 1] < s[a[i + 1] - 1])
        {
            ++tag[a[i]];
            --tag[a[i + 1]];
        }
    for(int i = 1; i <= n; ++i)
    {
        tag[i] += tag[i - 1];
        if(tag[i])
            ans += s[i] - s[i - 1];
        else
            ans += 0.5;
    }
    printf("%.3f\n", ans - 1e-3);
    printf("%.3f\n", ans);
    printf("%.3f\n", ans + 1e-3);
    return 0;
}
