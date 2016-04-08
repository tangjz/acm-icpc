/*
ID: tangjin2
LANG: C++
TASK: fracdec
*/
#include <cstdio>
const int maxd = 100002;
int n, d, tot, seq[maxd], idx[maxd], cnt;
int main()
{
	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);
	scanf("%d%d", &n, &d);
	cnt += printf("%d.", n / d);
	n %= d;
	idx[n] = ++tot;
	while(1)
	{
		n *= 10;
		seq[++tot] = n / d;
		n %= d;
		if(idx[n])
		{
			for(int i = 2; i <= idx[n]; ++i)
			{
				cnt += printf("%d", seq[i]);
				if(cnt == 76)
				{
					putchar('\n');
					cnt = 0;
				}
			}
			if(n)
			{
				putchar('(');
				if(++cnt == 76)
				{
					putchar('\n');
					cnt = 0;
				}
				for(int i = idx[n] + 1; i <= tot; ++i)
				{
					cnt += printf("%d", seq[i]);
					if(cnt == 76)
					{
						putchar('\n');
						cnt = 0;
					}
				}
				putchar(')');
				if(++cnt == 76)
				{
					putchar('\n');
					cnt = 0;
				}
			}
			else if(idx[n] == 1)
			{
				putchar('0');
				if(++cnt == 76)
				{
					putchar('\n');
					cnt = 0;
				}
			}
			if(cnt)
				putchar('\n');
			break;
		}
		idx[n] = tot;
	}
	return 0;
}
