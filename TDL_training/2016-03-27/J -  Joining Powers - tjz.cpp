#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 45, maxv = 60;
int n, a[maxn];
LL f[maxn][maxv][2], coeff[maxv];
void preDP()
{
    memset(f[0], 0, sizeof f[0]);
    f[0][1][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        memcpy(f[i], f[i - 1], sizeof f[0]);
        for(int j = 1; j < maxv; ++j)
        {
            int k = j * a[i] / __gcd(j, a[i]);
            if(k > maxv)
                continue;
            f[i][k][0] += f[i - 1][j][1];
            f[i][k][1] += f[i - 1][j][0];
        }
    }
    coeff[0] = 0; // set for lcm >= maxv
    for(int i = 1; i < maxv; ++i)
    {
        coeff[i] = f[n][i][1] - f[n][i][0];
        coeff[0] -= coeff[i];
        // printf("%d : %I64d\n", i, coeff[i]);
    }
    ++coeff[1]; // remove empty set
}
LL solve(LL M)
{
    LL ret = coeff[0];
    for(int i = 1; i < maxv; ++i)
    {
        LL v = pow(M, 1.0 / i);
        // avoid eps
        while(1)
        {
            LL tM = 1;
            for(int j = 0; j < i; ++j)
                if(tM <= M / (v + 1))
                    tM *= v + 1;
                else
                {
                    tM = M + 1;
                    break;
                }
            if(tM > M)
                break;
            ++v;
        }
        while(1)
        {
            LL tM = 1;
            for(int j = 0; j < i; ++j)
                if(tM <= M / v)
                    tM *= v;
                else
                {
                    tM = M + 1;
                    break;
                }
            if(tM <= M)
                break;
            --v;
        }
        ret += v * coeff[i];
    }
    return ret;
}
int main()
{
    int t, m;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &m, &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        preDP();
        LL L = 1, R = (LL)1e17, M;
        while(L < R)
        {
            M = L + R >> 1;
            if(solve(M) >= m)
                R = M;
            else
                L = M + 1;
        }
        printf("%lld\n", L);
    }
    return 0;
}
