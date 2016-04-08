/*
 * i的出现次数为f[i]
 * f[0] = 1
 * f[j + k] += f[j] (1 <= k <= s[i])
 */
#include <cstdio>
using namespace std;
int s[3], f[81] = {}, v, ans = 0;
int main()
{
	int i, j, k;
	scanf("%d%d%d", &s[0], &s[1], &s[2]);
	f[0] = 1;
	for(i = 0; i < 3; ++i)
	{
		v += s[i];
		for(j = v; j >= 0; --j)
			if(f[j])
			{
				for(k = 1; k <= s[i]; ++k) f[j + k] += f[j];
				f[j] = 0;
			}
	}
	for(i = 1; i <= v; ++i)
		if(f[i] > f[ans]) ans = i;
	printf("%d\n", ans);
	return 0;
}
