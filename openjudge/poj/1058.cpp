#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 5001, maxs = 5, maxp = 10;
int m, len, mod, ans;
LL n;
struct Matrix
{
	int r, c, num[maxs][maxs];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix operator * (const int &t) const
	{
		Matrix ret = {r, c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				ret.num[i][j] = (LL)num[i][j] * t % mod;
		return ret;
	}
	Matrix inc()
	{
		Matrix ret = *this;
		for(int i = 0; i < r; ++i)
			if(++ret.num[i][i] >= mod)
				ret.num[i][i] -= mod;
		return ret;
	}
	Matrix pow(LL k)
	{
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A;
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int origin()
{
	int cnt = 0, tmp = mod - 1;
	static int fact[maxp];
	for(int i = 2; (LL)i * i <= tmp; ++i)
		if(tmp % i == 0)
		{
			fact[cnt++] = i;
			do tmp /= i; while(tmp % i == 0);
		}
	if(tmp > 1)
		fact[cnt++] = tmp;
	for(int ori = 2; ; ++ori)
	{
		bool flag = 1;
		for(int i = 0; i < cnt && flag; ++i)
			flag &= mod_pow(ori, (mod - 1) / fact[i]) != 1;
		if(flag)
			return ori;
	}
}
int main()
{
	for(int tot, sta, ter, w; scanf("%d%lld%d%d", &m, &n, &len, &mod) == 4; )
	{
		memset(&A, 0, sizeof(Matrix));
		A.r = A.c = m;
		scanf("%d%d%d", &tot, &sta, &ter);
		--sta;
		--ter;
		for(int u, v; tot--; )
		{
			scanf("%d%d", &u, &v);
			++A.num[--u][--v];
		}
		ans = 0;
		w = mod_pow(origin(), (mod - 1) / len);
		for(int i = 0, ww = 1; i < len; ++i, ww = (LL)ww * w % mod)
			if((ans += (A * ww).inc().pow(n).num[sta][ter]) >= mod)
				ans -= mod;
		ans = (LL)ans * mod_inv(len) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
