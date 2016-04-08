/*
 * ´ÓµÍµ½¸ß g[j] = f[i - delta] + sun[j][i] , f[i] = max(g[j])
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n, h, delta, sum[2001][2001] = {}, f[2001] = {}, g[2001] = {};
int main()
{
    int i, j, cnt;
    scanf("%d%d%d", &n, &h, &delta);
    for(i = 0; i < n; ++i)
    {
        scanf("%d", &cnt);
        while(cnt--)
        {
            scanf("%d", &j);
            ++sum[i][j];
        }
    }
    for(i = 1; i <= h; ++i)
        for(j = 0; j < n; ++j)
        {
            if(i >= delta) g[j] = max(g[j], f[i - delta]);
            g[j] += sum[j][i];
            f[i] = max(f[i], g[j]);
        }
    printf("%d\n", f[h]);
    return 0;
}
