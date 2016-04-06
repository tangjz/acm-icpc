#include <cstdio>
#include <cstring>
const int maxs = 100010;
int n, len, cnt[maxs >> 1];
char s[maxs];
void swap(char &x, char &y)
{
	char z = x;
	x = y;
	y = z;
}
int main()
{
	while(scanf("%s%d", s, &n) == 2)
	{
		memset(cnt, 0, sizeof cnt);
		while(n--)
		{
			int x;
			scanf("%d", &x);
			cnt[x] ^= 1;
		}
		len = strlen(s);
		for(int i = 1, j = 0; i <= len >> 1; ++i)
		{
			j ^= cnt[i];
			if(j)
				swap(s[i - 1], s[len - i]);
		}
		puts(s);
	}
	return 0;
}
