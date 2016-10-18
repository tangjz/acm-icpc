#include <stdio.h>
#include <cstring>
const int maxn = 100001, maxd = 26;
int len[3], cnt[3][maxd], aL, aR;
char str[3][maxn];
int main()
{
	for(int i = 0; i < 3; ++i)
	{
		scanf("%s", str[i]);
		len[i] = strlen(str[i]);
		for(int j = 0; j < len[i]; ++j)
			++cnt[i][str[i][j] - 'a'];
	}
	for(int i = 0; i * len[1] <= len[0]; ++i)
	{
		bool flag = 1;
		for(int j = 0; j < maxd && flag; ++j)
			flag &= i * cnt[1][j] <= cnt[0][j];
		if(!flag)
			continue;
		int tmp = 0x3f3f3f3f;
		for(int j = 0; j < maxd; ++j)
			if(cnt[2][j])
			{
				int val = (cnt[0][j] - i * cnt[1][j]) / cnt[2][j];
				if(tmp > val)
					tmp = val;
			}
		if(aL + aR < i + tmp)
		{
			aL = i;
			aR = tmp;
		}
	}
	for(int i = 0; i < aL; ++i)
		printf("%s", str[1]);
	for(int i = 0; i < aR; ++i)
		printf("%s", str[2]);
	for(int i = 0; i < maxd; ++i)
	{
		cnt[0][i] -= aL * cnt[1][i] + aR * cnt[2][i];
		for(int j = 0; j < cnt[0][i]; ++j)
			putchar('a' + i);
	}
	putchar('\n');
	return 0;
}
