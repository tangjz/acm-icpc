#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, k;
int fish1[100101] = {}, fish2[100101] = {};
bool cmp(const int &x, const int &y) { return x > y; }
int main()
{
    int i;
    scanf("%d%d%d", &n, &m, &k);
    for(i = 0; i < n; ++i) scanf("%d", &fish1[i]);
    for(i = 0; i < m; ++i) scanf("%d", &fish2[i]);
    sort(fish1, fish1 + n, cmp);
    sort(fish2, fish2 + m, cmp);
    if(n > m) { printf("YES\n"); return 0; }
    for(i = 0; i < n; ++i) if(fish1[i] > fish2[i]) break;
    if(i < n) printf("YES\n");
    else printf("NO\n");
    return 0;
}
