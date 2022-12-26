#include <cstdio>
int day, ans;
int main()
{
	for(int i = 1, j, k; i < 8; ++i)
	{
		scanf("%d%d", &j, &k);
		if(j + k > 8 && j + k > ans) ans = j + k, day = i;
	}
	printf("%d\n", day);
}
