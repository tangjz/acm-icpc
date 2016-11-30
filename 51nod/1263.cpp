#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 32000, maxp = 35;
int tot, pr[maxn], dr[maxn];
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	for(x %= p; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int FP;
struct Matrix
{
	int r, c, num[2][2];
	bool operator == (const Matrix &x) const
	{
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				if(num[i][j] != x.num[i][j])
					return 0;
		return 1;
	}
	Matrix operator * (const Matrix &x) const
	{
		Matrix ret = {r, x.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * x.num[j][k]) % FP;
		return ret;
	}
	Matrix pow(LL k)
	{
		Matrix ret = (Matrix){r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A, B;
bool test(int a, int b, int p, LL n)
{
	A = (Matrix){1, 2, 1, 1, 0, 0};
	B = (Matrix){2, 2, 0, b % p, 1, a % p};
	FP = p;
	return A == A * B.pow(n);
}
void decomposition(int val, int &cnt, int pri[])
{
	for(int i = 0; i < tot && (LL)pr[i] * pr[i] <= val; ++i)
		for( ; val % pr[i] == 0; pri[cnt++] = pr[i], val /= pr[i]);
	if(val > 1)
		pri[cnt++] = val;
}
LL solve(int a, int b, int p, int pp) // f(n) = a f(n-1) + b f(n-2) mod p^k
{
	int dt = ((LL)a * a + 4LL * b) % p;
	LL ret;
	int cnt = 0, pri[maxp];
	if(p == 2)
	{
		ret = 6;
		pri[cnt++] = 2;
		pri[cnt++] = 3;
	}
	else if(dt != 0)
	{
		if(mod_pow(dt, (p - 1) >> 1, p) == 1)
		{
			ret = p - 1;
			decomposition(ret, cnt, pri);
		}
		else
		{
			ret = (LL)p * p - 1;
			decomposition(p + 1, cnt, pri);
			decomposition(p - 1, cnt, pri);
		}
	}
	else
	{
		ret = (LL)p * (p - 1);
		decomposition(p - 1, cnt, pri);
		pri[cnt++] = p;
	}
	for(int pr = p; p < pp; p *= pr, ret *= pr, pri[cnt++] = pr);
	sort(pri, pri + cnt);
	for(int i = 0, j; i < cnt; i = j)
	{
		int c = 1;
		for(j = i + 1; j < cnt && pri[i] == pri[j]; ++j, ++c);
		for( ; c > 0 && test(a, b, pp, ret / pri[i]); --c, ret /= pri[i]);
	}
	return test(a, b, pp, ret) ? ret : -1;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!dr[i])
			pr[tot++] = dr[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			dr[k] = pr[j];
			if(dr[i] == pr[j])
				break;
		}
	}
	int t, a, b, n;
	scanf("%d", &t);
	while(t--)
	{
		LL ans = 1;
		scanf("%d%d%d", &a, &b, &n);
		int cnt = 0, p[maxp];
		decomposition(n, cnt, p);
		sort(p, p + cnt);
		for(int i = 0, j; i < cnt; i = j)
		{
			int pp = p[i];
			for(j = i + 1; j < cnt && p[i] == p[j]; ++j, pp *= p[i]);
			LL cir = solve(a % pp, b % pp, p[i], pp);
			if(cir != -1)
				ans = ans / __gcd(ans, cir) * cir;
			else
			{
				ans = -1;
				break;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
