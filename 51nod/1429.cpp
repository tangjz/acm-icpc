#include <stdio.h>
int x[2][2], c[2][2], ans;
int main()
{
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
		{
			scanf("%d", x[i] + j);
			for( ; x[i][j] % 2 == 0; ++c[i][0], x[i][j] >>= 1);
			for( ; x[i][j] % 3 == 0; ++c[i][1], x[i][j] /= 3);
		}
	if((long long)x[0][0] * x[0][1] == (long long)x[1][0] * x[1][1])
	{
		if(c[0][1] < c[1][1])
		{
			ans = c[1][1] - c[0][1];
			c[1][0] += ans;
		}
		else
		{
			ans = c[0][1] - c[1][1];
			c[0][0] += ans;
		}
		ans += c[0][0] < c[1][0] ? c[1][0] - c[0][0] : c[0][0] - c[1][0];
		printf("%d\n", ans);
	}
	else
		puts("-1");
	return 0;
}
