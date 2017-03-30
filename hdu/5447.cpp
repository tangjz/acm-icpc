#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxn = 1000001;
typedef long double DB;
int tot, pr[maxn], d[maxn];
int t, ans1, ans2;
__int128_t v1, v2;
template<class T> void read(T &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
bool issqr(__int128_t x)
{
	__int128_t y = (__int128_t)ceil(sqrt((DB)x));
	for( ; y * y <= x; ++y);
	for(--y; y * y > x; --y);
	return y * y == x;
}
bool iscub(__int128_t x)
{
	__int128_t y = (__int128_t)ceil(pow((DB)x, 1.0 / 3));
	for( ; y * y * y <= x; ++y);
	for(--y; y * y * y > x; --y);
	return y * y * y == x;
}
void upd(int &ans, __int128_t L, __int128_t R)
{
	if(R == 1)
		ans *= L == 1 ? 1 : (iscub(L) ? 3 : (issqr(L) ? 2 : 1)); // (1, 1), (p1^3, 1), (p1^2, 1), (p1, 1)
	else if(issqr(R))
		ans *= R % L ? 2 : 3; // (p1, p2^2), (p1, p1^2)
	else if(issqr(L)) // r > 1
		ans *= L % R ? 2 : 3; // (p1^2, p2), (p1^2, p1)
	else if(R % L == 0)
		ans *= L == R ? 2 : 2; // (p1, p1), (p1, p1 p2)
	else if(L < R)
		ans *= 1; // (p1, p2 p3)
	else
		ans *= 1; // (p1, p2), (p1 p3, p2)
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	read(t);
	while(t--)
	{
		read(v1);
		read(v2);
		ans1 = ans2 = 1;
		for(int i = 0; i < tot; ++i)
		{
			if(v1 % pr[i] == 0)
			{
				int cnt = 0;
				for( ; v1 % pr[i] == 0; v1 /= pr[i], ++cnt);
				ans1 *= cnt;
			}
			if(v2 % pr[i] == 0)
			{
				int cnt = 0;
				for( ; v2 % pr[i] == 0; v2 /= pr[i], ++cnt);
				ans2 *= cnt;
			}
		}
		__int128_t r = std::__gcd(v1, v2);
		upd(ans1, r, v1 / r);
		upd(ans2, r, v2 / r);
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
