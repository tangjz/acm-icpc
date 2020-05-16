#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n;
struct Node
{
    int x;
    bool operator < (const Node &t) const
    {
        printf("1 %d %d\n", x, t.x);
        fflush(stdout);
        char str[5];
        scanf("%s", str);
        return str[0] == 'Y';
    }
} a[maxn];
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        a[i].x = i + 1;
    stable_sort(a, a + n);
    printf("0");
    for(int i = 0; i < n; ++i)
        printf(" %d", a[i].x);
    printf("\n");
    return 0;
}
