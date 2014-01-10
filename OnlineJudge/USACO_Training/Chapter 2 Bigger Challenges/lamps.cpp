/*
ID: tangjin2
LANG: C++
TASK: lamps
*/
#include <cstdio>
const int transformed[] = {63, 42, 21, 36};
int n, c, i, j, k;
bool on[7], off[7], light[64], succeed;
char ch[10];
void make_bit(char *s, int num, int len)
{
	s[len] = '\0';
	while(len--) s[len] = (num & 1) + '0', num >>= 1;
}
void dfs(int level, int start, int cnt)
{
	if(level >= 5) return;
	if(cnt <= c)
	{
		for(i = 1; i <= 6; ++i) if(on[i] && !((start >> (6 - i)) & 1) || off[i] && ((start >> (6 - i)) & 1)) break;
		if(i > 6) light[start] = succeed = 1;
	}
	dfs(level + 1, start ^ transformed[level], cnt + 1);
	dfs(level + 1, start, cnt);
}
int main()
{
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	scanf("%d%d%d", &n, &c, &k);
	while(k != -1)
	{
		k = (k - 1) % 6 + 1;
		on[k] = 1;
		scanf("%d", &k);
	}
	scanf("%d", &k);
	while(k != -1)
	{
		k = (k - 1) % 6 + 1;
		off[k] = 1;
		scanf("%d", &k);
	}
	dfs(0, 63, 0);
	if(!succeed) puts("IMPOSSIBLE");
	else
		for(i = 0; i <= 63; ++i)
			if(light[i])
			{
				make_bit(ch, i, 6);
				for(j = n / 6; j; --j) printf("%s", ch);
				if(n % 6 != 0)
				{
					k = i >> (6 - (n % 6));
					make_bit(ch, k, n % 6);
					printf("%s", ch);
				}
				putchar('\n');
			}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
