#include <stdio.h>
const int maxd = 30;
int n, m, f[2], ans;
int main()
{
	scanf("%d%d", &n, &m);
	f[1] = (1 << maxd) - 1;
	for(int i = 1; i <= n; ++i)
	{
		int val;
		char op[4];
		scanf("%s%d", op, &val);
		for(int j = 0; j < 2; ++j)
			switch(op[0])
			{
				case 'O' : f[j] |= val; break;
				case 'X' : f[j] ^= val; break;
				case 'A' : f[j] &= val;
			}
	}
	for(int i = maxd - 1, o = 0; i >= 0; --i)
	{
		int k = 0, mx = (f[0] >> i) & 1;
		if((o || ((m >> i) & 1)) && mx < ((f[1] >> i) & 1))
		{
			k = 1;
			mx = (f[1] >> i) & 1;
		}
		ans |= mx << i;
		o |= ((m >> i) & 1) && !k;
	}
	printf("%d\n", ans);
	return 0;
}
