#include <cstdio>
const int mod = 1000000007;
int n, m, val, ans = mod + 1 >> 1;
int main()
{
	scanf("%d%d ", &n, &m);
	while(n--)
	{
		val = ((val << 3) + (val << 1) + (getchar() - '0')) % m;
		if(!val)
		{
			ans <<= 1;
			if(ans >= mod)
				ans -= mod;
		}
	}
	printf("%d\n", val ? 0 : ans);
	return 0;
}
