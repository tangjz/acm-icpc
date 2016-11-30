#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
bool isprime(int x)
{
	if(x < 2)
		return 0;
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
bool issqu(int x)
{
	int t = (int)(sqrt(x) + 1e-4);
	return x == t * t;
}
bool iscube(int x)
{
	int t = (int)(pow(x, 1.0 / 3) + 1e-4);
	return x == t * t * t;
}
bool isquad(int x)
{
	int t = (int)(sqrt(sqrt(x)) + 1e-4);
	return x == t * t * t * t;
}
bool issummul(int x)
{
	int t = x, c = 0;
	while(t)
	{
		c += t % 10;
		t /= 10;
	}
	return x % c == 0;
}
bool ismulmul(int x)
{
	int t = x, s = 1;
	while(t)
	{
		s *= t % 10;
		t /= 10;
	}
	return s && x % s == 0;
}
bool isfact(int x, int y)
{
	return y % x == 0;
}
bool ismul(int x, int y)
{
	return x % y == 0;
}
bool isothsqu(int x, int y)
{
	int t = (int)(sqrt(x) + 1e-4);
	return x == t * t && y == t;
}
bool isothcube(int x, int y)
{
	int t = (int)(pow(x, 1.0 / 3) + 1e-4);
	return x == t * t * t && y == t;
}
bool isothquad(int x, int y)
{
	int t = (int)(sqrt(sqrt(x)) + 1e-4);
	return x == t * t * t * t && y == t;
}
bool isothsummul(int x, int y)
{
	int t = y, c = 0;
	while(t)
	{
		c += t % 10;
		t /= 10;
	}
	return x % c == 0;
}
bool isothmulmul(int x, int y)
{
	int t = y, s = 1;
	while(t)
	{
		s *= t % 10;
		t /= 10;
	}
	return s && x % s == 0;
}
const int maxn = 101;
int t, n, num[maxn], cnt[maxn], ans, tot, out[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", num + i);
		for(int i = 0; i < n; ++i)
		{
			cnt[i] = isprime(num[i]) + issqu(num[i]) + iscube(num[i]) + isquad(num[i]) + issummul(num[i]) + ismulmul(num[i]);
			for(int j = 0; j < n; ++j)
				if(i != j)
					cnt[i] += isfact(num[i], num[j]) + ismul(num[i], num[j]) + isothsqu(num[i], num[j]) + isothcube(num[i], num[j]) + isothquad(num[i], num[j]) + isothsummul(num[i], num[j]) + isothmulmul(num[i], num[j]);
		}
		ans = cnt[0];
		for(int i = 1; i < n; ++i)
			if(ans < cnt[i])
				ans = cnt[i];
		tot = 0;
		for(int i = 0; i < n; ++i)
			if(ans == cnt[i])
				out[tot++] = num[i];
		sort(out, out + tot);
		printf("DATA SET #%d\n", Case);
		for(int i = 0; i < tot; ++i)
			printf("%d\n", out[i]);
	}
	return 0;
}
