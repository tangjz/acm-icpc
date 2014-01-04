/*
ID: tangjin2
LANG: C++
TASK: friday
*/
#include <cstdio>
int n, w = 3, used[7];
int main()
{
	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1900; i <= 1900 + n - 1; ++i)
		for(int j = 0; j < 12; ++j)
			if(j == 2)
				if(i % 400 == 0 || i % 4 == 0 && i % 100 != 0)
				{
					w = (w + 1) % 7;
					++used[w];
				}
				else ++used[w];
			else if(j == 0 || j == 1 || j == 3 || j == 5 || j == 7 || j == 8 || j == 10)
			{
				w = (w + 3) % 7;
				++used[w];
			}
			else
			{
				w = (w + 2) % 7;
				++used[w];
			}
	printf("%d %d %d %d %d %d %d\n", used[6], used[0], used[1], used[2], used[3], used[4], used[5]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
