/*
ID: tangjin2
LANG: C++
TASK: beads
*/
#include <cstdio>
char a[350];
int Max, n;
int main()
{
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);
	int temp, flag1, flag2;
	char color1, color2;
	scanf("%d%s", &n, a);
	for(int i = 0, j, k; i < n; ++i)
	{
		temp = flag1 = flag2 = 0;
		j = i - 1;
		if(j < 0) j += n;
		color1 = a[j];
		k = i;
		color2 = a[k];
		while(j != k)
		{
			if(flag1 && flag2) break;
			if(!flag1)
			{
				if(j == k) break;
				if(a[j] == 'w') ++temp;
				else if(color1 == 'w') color1 = a[j], ++temp;
				else if(a[j] == color1) ++temp;
				else flag1 = 1;
				--j;
				if(j < 0) j += n;
			}
			if(!flag2)
			{
				if(j == k) break;
				if(a[k] == 'w') ++temp;
				else if(color2 == 'w') color2 = a[k], ++temp;
				else if(a[k] == color2) ++temp;
				else flag2 = 1;
				++k;
				if(k == n) k -= n;
			}
		}
		if(!(flag1 && flag2))
		{
			if(a[k] == 'w') ++temp;
			else if(color1 == 'w' || color2 == 'w') ++temp;
			else if(a[k] == color1 || a[k] == color2) ++temp;
		}
		if(temp > Max) Max = temp;
	}
	printf("%d\n", Max);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
