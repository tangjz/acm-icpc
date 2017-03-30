#include <stdio.h>
const int maxn = 26;
int fir[maxn], pos;
char str[maxn + 5], out[2][maxn + 1];
int main()
{
	scanf("%s", str + 1);
	for(int i = 1; i <= maxn + 1; ++i)
	{
		str[i] -= 'A';
		if(!fir[str[i]])
			fir[str[i]] = i;
		else
			pos = i;
	}
	int len = pos - fir[str[pos]] - 1;
	if(!len)
	{
		puts("Impossible");
		return 0;
	}
	int half = len >> 1;
	out[0][half] = str[pos] + 'A';
	{ // before fir[str[pos]]
		int x = 0, y = half;
		for(int i = fir[str[pos]] - 1; i > 0; --i)
		{
			if(x == 0)
			{
				if(y + 1 < maxn >> 1)
					++y;
				else
					++x;
			}
			else
			{
				if(y - 1 >= 0)
					--y;
				else
					--x;
			}
			out[x][y] = str[i] + 'A';
		}
	}
	{ // after fir[str[pos]]
		int x = 0, y = half;
		for(int i = fir[str[pos]] + 1; i <= maxn + 1; ++i)
		{
			if(i == pos)
				continue;
			if(x == 0)
			{
				if(y - 1 >= 0)
					--y;
				else
					++x;
			}
			else
			{
				if(y + 1 < maxn >> 1)
					++y;
				else
					--x;
			}
			out[x][y] = str[i] + 'A';
		}
	}
	for(int i = 0; i < 2; ++i)
		puts(out[i]);
	return 0;
}
