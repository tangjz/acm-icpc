#include <cstdio>
const int mod = 998244353;
int n, cnt, sum, ans;
char op[3];
int main()
{
	scanf("%d", &n);
	cnt = sum = ans = 1;
	for(int i = 2; i <= n; ++i)
	{
		scanf("%s", op);
		if(op[0] == '&')
			++cnt;
		else
		{
			sum = (long long)sum * cnt % mod;
			cnt = 1;
			(ans += sum) >= mod && (ans -= mod);
		}
	}
	sum = (long long)sum * cnt % mod;
	(ans += sum) >= mod && (ans -= mod);
	printf("%d\n", ans);
	return 0;
}
