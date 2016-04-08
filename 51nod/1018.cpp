#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 50000;
int n, a[maxn];
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    sort(a, a + n);
    for(int i = 0; i < n; ++i)
        printf("%d\n", a[i]);
    return 0;
}
