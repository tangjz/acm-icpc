#include <stdio.h>
int t, n, m, ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n <= m)
		{
			printf("%d\n", m - n);
			continue;
		}
		ans = 0x3f3f3f3f;
		int pw = 0, cnt = 0;
		for( ; 1 << pw <= n - m; ++pw);
		for(int i = 0; ; ++i)
		{
			int tmp = n - (1 << pw) + 1;
			if(tmp < 0)
				tmp = 0;
			int cst = m - tmp;
			if(cst < i)
				cst = i;
			if(ans > cnt + cst + pw)
				ans = cnt + cst + pw;
			if(tmp == m)
				break;
			n -= (1 << pw - 1) - 1;
			cnt += pw - 1;
			for( ; pw && (1 << pw - 1) > n - m; --pw);
		}
		printf("%d\n", ans);
	}
	return 0;
}
