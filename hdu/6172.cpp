#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 2, mod = 1000000007, inv2 = (mod + 1) >> 1;
struct Matrix
{
    int r, c, num[maxs][maxs];
    Matrix operator * (const Matrix &x) const
    {
        Matrix ret = {};
        ret.r = r;
        ret.c = x.c;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < x.c; ++j)
            {
                LL tmp = 0;
                for(int k = 0; k < c; ++k)
                    tmp += (LL)num[i][k] * x.num[k][j];
                ret.num[i][j] = tmp % mod;
            }
        return ret;
    }
    Matrix pow(LL k) const
    {
        Matrix ret = {}, tmp = *this;
        ret.r = ret.c = r;
        for(int i = 0; i < r; ++i)
            ret.num[i][i] = 1;
        while(k)
        {
            if(k & 1)
                ret = ret * tmp;
            tmp = tmp * tmp;
            k >>= 1;
        }
        return ret;
    }
} A, B, C;
int t;
LL n;
int main()
{
    A.r = 1, A.c = 2, A.num[0][0] = 1, A.num[0][1] = 0;
    B.r = 2, B.c = 2, B.num[0][0] = inv2 + 3, B.num[0][1] = inv2, B.num[1][0] = inv2 + 16, B.num[1][1] = inv2 + 3;
    C.r = 2, C.c = 1, C.num[0][0] = 1, C.num[1][0] = 3;
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d", &n);
        Matrix ans = A * B.pow(n) * C;
        printf("%d\n", ans.num[0][0]);
    }
    return 0;
}