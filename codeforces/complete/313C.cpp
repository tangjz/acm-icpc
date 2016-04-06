#include <cstdio>
#include <algorithm>
using namespace std;
int n;
long long num[2000001], ans = 0;
int main()
{
    int m = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%I64d", &num[i]), ans += num[i];
    sort(num, num + n);
    while(1 << (2 * m) < n) ++m;
    for(int i = 0; i < m; ++i)
    {
        int limit = 1 << (2 * i);
        for(int j = 1; j <= limit; ++j) ans += num[n - j];
    }
    printf("%I64d\n", ans);
    return 0;
}
