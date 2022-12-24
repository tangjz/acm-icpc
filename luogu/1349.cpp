#include <cstdio>
int p, q, a1, a2;
long long n, mod;
struct Matrix
{
    int r, c; long long num[2][2];
    Matrix(void) { r = c = 0; num[0][0] = num[0][1] = num[1][0] = num[1][1] = 0; }
    Matrix operator * (const Matrix &x) const
    {
        Matrix temp;
        temp.r = r; temp.c = x.c;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                for(int k = 0; k < x.c; ++k) temp.num[i][k] = (temp.num[i][k] + num[i][j] * x.num[j][k]) % mod;
        return temp;
    }
    Matrix operator *= (const Matrix &x) { return *this = *this * x; }
} ans, sum;
int main()
{
    scanf("%d%d%d%d%lld%lld", &p, &q, &a1, &a2, &n, &mod);
	p %= mod;
	q %= mod;
	a1 %= mod;
	a2 %= mod;
    if(n == 1) printf("%d\n", a1);
    else if(n == 2) printf("%d\n", a2);
    else
    {
        n -= 2;
    	ans.r = 1, ans.c = 2, ans.num[0][0] = a1, ans.num[0][1] = a2;
        sum.r = sum.c = 2, sum.num[0][1] = q, sum.num[1][0] = 1 % mod, sum.num[1][1] = p;
        while(n)
        {
            if(n & 1) ans *= sum;
            sum *= sum;
            n >>= 1;
        }
        printf("%lld\n", ans.num[0][1]);
    }
}