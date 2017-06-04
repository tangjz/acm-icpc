#include <stdio.h>
typedef long long LL;
const int maxn = 5001, mod = 1000000007;
int n, typ[maxn], f[maxn];
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int main()
{
	scanf("%d", &n);
	{ // init
		int c1, c2, x;
		scanf("%d%d", &c1, &c2);
		while(c1--)
		{
			scanf("%d", &x);
			typ[x] |= 2; // a[x-1] > a[x]
			typ[x + 1] |= 1; // a[x] < a[x+1]
		}
		while(c2--)
		{
			scanf("%d", &x);
			typ[x] |= 1; // a[x-1] < a[x]
			typ[x + 1] |= 2; // a[x] > a[x+1]
		}
		for(int i = 1; i < n; ++i)
			if(typ[i] == 3)
			{
				puts("0");
				return 0;
			}
	}
	f[0] = 1;
	for(int i = 1; i < n; ++i)
	{
		int sum = 0;
		if(typ[i] == 1)
		{
			for(int j = 0, pre = 0; j <= i; ++j, pre = sum)
			{
				mod_inc(sum, f[j]);
				f[j] = pre;
			}
		}
		else if(typ[i] == 2)
		{
			for(int j = i; j >= 0; --j)
			{
				mod_inc(sum, f[j]);
				f[j] = sum;
			}
		}
		else
		{
			for(int j = 0; j < i; ++j)
				mod_inc(sum, f[j]);
			for(int j = 0; j <= i; ++j)
				f[j] = sum;
		}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i)
		mod_inc(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
