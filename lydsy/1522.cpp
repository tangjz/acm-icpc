#include <stdio.h>
const int maxn = 51;
int n;
unsigned int a[maxn];
unsigned long long f[3], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%u", a + i);
	for(int i = 31; i >= 0; --i)
	{
		int o = 0;
		unsigned int all = (1u << i) - 1;
		f[0] = 1;
		f[1] = f[2] = 0;
		for(int j = 0; j < n; ++j)
		{
			unsigned int val = (a[j] & all) + 1;
			if((a[j] >> i) & 1)
			{
				unsigned long long tmp[2] = {f[0] + (f[2] << i), f[1] << i};
				o ^= 1;
				f[0] *= val;
				f[1] = f[1] * val + tmp[0];
				f[2] = f[2] * val + tmp[1];
			}
			else
			{
				f[0] *= val;
				f[1] *= val;
				f[2] *= val;
			}
		}
		ans += f[1 + (o ^ 1)];
		if(o)
		{
			--ans;
			break;
		}
	}
	printf("%llu\n", ans);
	return 0;
}
