#include <cstdio>
#include <cstring>
const int maxn = 1000002;
int n, pre[maxn], suf[maxn];
char str[maxn];
int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = 1; i <= n; ++i)
        pre[i] = pre[i - 1] + (str[i] == '0');
    for(int i = n; i >= 1; --i)
        suf[i] = suf[i + 1] + (str[i] == '1');
    for(int i = 0; i <= n; ++i)
        if(pre[i] == suf[i + 1])
        {
            printf("%d\n", i);
            return 0;
        }
    puts("-1");
    return 0;
}
