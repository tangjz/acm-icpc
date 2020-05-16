#include <cstdio>
int n, m, a, b, ans;
bool flag;
int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    ans = (n / a) * (m / b);
    if(n % a)
    {
        int c = m / b, d = a / (n % a), e = (c - 1) / d + 1;
        if(c < e * d)
            flag = 1;
        ans += e;
    }
    if(m % b)
    {
        int c = n / a, d = b / (m % b), e = (c - 1) / d + 1;
        if(c < e * d)
            flag = 1;
        ans += e;
    }
    if(n % a && m % b && !flag)
        ++ans;
    printf("%d\n", ans);
    return 0;
}
