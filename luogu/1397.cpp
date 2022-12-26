#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 1000010;
const LL mod = 1000000007;
int nlen, mlen;
char n[maxn], m[maxn];
LL a, b, c, d;
struct Matrix
{
	LL a, b;
	Matrix operator * (const Matrix &x) const { return (Matrix){a * x.a % mod, (b * x.a + x.b) % mod}; }
	void operator *= (const Matrix &x) { *this = *this * x; }
	Matrix pow10() const
	{
		int n = 10;
		Matrix ans = (Matrix){1, 0}, sum = *this;
		while(n)
		{
			if(n & 1) ans *= sum;
			sum *= sum;
			n >>= 1;
		}
		return ans;
	}
} A[11], B[11], SA, SB;

int main()
{
	int i;
	scanf("%s%s%lld%lld%lld%lld", n, m, &a, &b, &c, &d);
	nlen = strlen(n); mlen = strlen(m);
	for(i = nlen - 1, --n[i]; i >= 0; --i)
	{
		if(n[i] < '0') --n[i - 1], n[i] += 10;
		n[i] -= '0';
	}
	for(i = mlen - 1, --m[i]; i >= 0; --i)
	{
		if(m[i] < '0') --m[i - 1], m[i] += 10;
		m[i] -= '0';
	}
	A[0] = B[0] = SA = SB = (Matrix){1, 0};
	A[1] = (Matrix){a, b};
	for(i = 2; i < 10; ++i) A[i] = A[1] * A[i - 1];
	for(i = 0; i < mlen; ++i) SA = SA.pow10() * A[(int)m[i]];
	B[1] = (Matrix){c, d};
	B[1] *= SA;
	for(i = 2; i < 10; ++i) B[i] = B[1] * B[i - 1];
	for(i = 0; i < nlen; ++i) SB = SB.pow10() * B[(int)n[i]];
	SA *= SB;
	printf("%lld\n", (SA.a + SA.b) % mod);
	return 0;
}
