#include <cstdio>
typedef long long LL;
int n, p, ans;
int main()
{
    scanf("%d%d", &n, &p);
    ans = 1;
    for(int i = 2; i <= n; ++i)
        ans = (LL)ans * i % p;
    printf("%d\n", ans);
	return 0;
}