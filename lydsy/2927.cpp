#include <stdio.h>
const int maxn = 50001;
int n, x, deg;
bool chk[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < 3; ++i)
	{
		scanf("%d", &x);
		chk[x] = 1;
	}
	for(int i = 3; i < n; ++i)
	{
		int cnt = 0;
		for(int j = 0; j < 3; ++j)
		{
			scanf("%d", &x);
			cnt += chk[x];
		}
		deg += cnt == 2;
	}
	puts(deg == 1 || !(n & 1) ? "TAK" : "NIE");
	return 0;
}
