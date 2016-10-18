#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 8000001;
const LL INF = (LL)1e10;
map<LL, LL> Hash;
int mu[maxn], t, v;
LL m;
LL calc_mu(LL x)
{
	if(x < maxn)
		return mu[x];
	if(Hash.count(x))
		return Hash[x];
	LL ret = 1;
	for(LL i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret -= calc_mu(x / i) * (j - i + 1);
	}
	return Hash[x] = ret;
}
LL calc_mu2(LL x)
{
	LL ret = 0;
	for(int i = 1, j, k = (int)sqrt(x); i <= k; i = j + 1)
	{
		j = (int)sqrt(x / (x / i / i));
		ret += (x / i / i) * (mu[j] - mu[i - 1]);
	}
	return ret;
}
LL calc(LL lim, int v)
{
	if(!v)
		return lim - calc_mu2(lim);
	else
	{
		LL c1 = calc_mu(lim), c2 = calc_mu2(lim);
		if(v == 1)
			return c1 + c2 >> 1;
		else
			return c2 - c1 >> 1;
	}
}
int main()
{
	mu[1] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		for(int j = i + i; j < maxn; j += i)
			mu[j] -= mu[i];
		mu[i] += mu[i - 1];
	}
	scanf("%d%I64d", &v, &m);
	LL L = 0, R = min(INF, m << 2), cL = 0, cR = calc(R, v);
	while(L + 1 < R)
	{
		LL M = (double)(m - cL) / (cR - cL) * (R - L) + L;
		if(M <= L)
			M = L + 1;
		else if(M >= R)
			M = R - 1;
		LL cM = calc(M, v);
		if(cM < m)
		{
			L = M;
			cL = cM;
		}
		else
		{
			R = M;
			cR = cM;
		}
	}
	printf("%I64d\n", R);
	return 0;
}
