#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxx = 2e9, maxsqx = 44722, maxc = 245;
int t, tot, prime[4648], ans_cnt, ans[maxc], x_L, x_H, l, r;
bool vis[maxsqx];
bool isprime(int x)
{
	if(x < 0 || x > maxx)
		return 0;
	if(x < maxsqx)
		return !vis[x];
	for(int i = 0, j = (int)sqrt(x); i < tot && prime[i] <= j; ++i)
		if(x % prime[i] == 0)
			return 0;
	return 1;
}
int main()
{
	for(int i = 2; i < maxsqx; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxsqx; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int A = 1; A <= 29; ++A)
		for(int B = 2; B <= 600; ++B)
			if(isprime(A + B) && isprime(A * (A + B) + B) && isprime(A * (A * (A + B) + B) + B))
			{
				long long now = (long long)A * (A * (A + B) + B) + B, tmp = (long long)(A + B) * (A * (A + B) + B) * (A * (A * (A + B) + B) + B);
				while(tmp <= maxx)
				{
					ans[++ans_cnt] = tmp;
					now = A * now + B;
					if(log10(tmp) + log10(now) > log10(2e9) || !isprime(now))
						break;
					tmp *= now;
				}
			}
	for(int A = 4; A <= 514; ++A)
		for(int B = max(3 - A, -511); B <= -1; ++B)
			if(isprime(A + B) && isprime(A * (A + B) + B) && isprime(A * (A * (A + B) + B) + B))
			{
				long long now = (long long)A * (A * (A + B) + B) + B, tmp = (long long)(A + B) * (A * (A + B) + B) * (A * (A * (A + B) + B) + B);
				while(tmp <= maxx)
				{
					ans[++ans_cnt] = tmp;
					now = A * now + B;
					if(log10(tmp) + log10(now) > log10(2e9) || !isprime(now))
						break;
					tmp *= now;
				}
			}
	sort(ans + 1, ans + ans_cnt + 1);
	ans[0] = 0, ans[ans_cnt + 1] = 2e9;
	scanf("%d", &t);
	while(t--)
	{
		int L, R, M;
		scanf("%d%d", &x_L, &x_H);
		L = 1, R = ans_cnt + 1;
		while(L < R)
		{
			M = L + R >> 1;
			if(x_L <= ans[M])
				R = M;
			else
				L = M + 1;
		}
		l = L;
		L = 0, R = ans_cnt;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if(x_H >= ans[M])
				L = M;
			else
				R = M - 1;
		}
		r = R;
		printf("%d\n", r - l + 1);
	}
	return 0;
}
