/*
ID: tangjin2
LANG: C++
TASK: palsquare
*/
#include <cstdio>
#include <cstring>
const char transform[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int num[18], num2[10], len, len2, n;
bool check()
{
	for(int i = 0; i < len >> 1; ++i) if(num[i] != num[len - 1 - i]) return 0;
	return 1;
}
int main()
{
	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);
	scanf("%d",&n);
	for(int i = 1, j; i <= 300; ++i)
	{
		j = i * i;
		memset(num, 0, sizeof num);
		len = 0;
		while(j)
		{
			num[len++] = j % n;
			j /= n;
		}
		if(check())
		{
			j = i;
			memset(num2, 0, sizeof num2);
			len2 = 0;
			while(j)
			{
				num2[len2++] = j % n;
				j /= n;
			}
			for(j = len2 - 1; j >= 0; --j) printf("%c", transform[num2[j]]);
			putchar(' ');
			for(j = len - 1; j >= 0; --j) printf("%c", transform[num[j]]);
			putchar('\n');
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
