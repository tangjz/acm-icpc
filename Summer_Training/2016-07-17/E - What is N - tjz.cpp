#include <iostream>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 100010;
const ULL INF = -1;
int tot, prime[maxn], phi[maxn];
int t, b, p;
ULL m, ans, preans;
int mod_pow(int x, int k)
{
	int ret = 1 % p;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int main()
{
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!phi[i])
		{
			phi[i] = i - 1;
			prime[tot++] = i;
		}
		for(int j = 0; j < tot && (LL)i * prime[j] < maxn; ++j)
			if(i % prime[j])
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			else
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
	}
	cin >> t;
	for(int Case = 1; Case <= t; ++Case)
	{
		cin >> b >> p >> m;
		ans = 0;
		int phi_p = phi[p], fact = 1;
		bool flag = 0, flag1 = 0;
		for(int n = 0; n < phi_p && n <= m; ++n)
		{
			if(mod_pow(n, flag ? fact + phi_p : fact) == b)
				++ans;
			if(!flag && (LL)fact * (n + 1) >= phi_p)
				flag = 1;
			fact = (LL)fact * (n + 1) % phi_p;
		}
		for(int n = 0; n < p; ++n)
		{
			int low = n < phi_p ? n + p : n;
			if(low > m)
				continue;
			if(mod_pow(n, fact + phi_p) == b)
			{
				preans = ans;
				ans += (m - low) / p + 1;
				if(preans > ans)
					flag1 = 1;
			}
		}
		if(flag1)
			cout << "Case #" << Case << ": " << "18446744073709551616" << endl;
		else
			cout << "Case #" << Case << ": " << ans << endl;
	}
	return 0;
}
