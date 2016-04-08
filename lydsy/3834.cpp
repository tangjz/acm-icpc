#include <cstdio>
int n, sL, sR, wL, wR, ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		ans = 1;
		scanf("%d%d%d%d", &sL, &sR, &wL, &wR);
		--sL, --wL;
		for(int i = sR < wR ? sR : wR, j; i; i = j)
		{
			if(sL / i < sR / i && wL / i < wR / i)
			{
				ans = i;
				break;
			}
			j = sR / (sR / i + 1) > wR / (wR / i + 1) ? sR / (sR / i + 1) : wR / (wR / i + 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
