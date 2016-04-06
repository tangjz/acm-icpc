#include <cstdio>
int t, flag, ans;
char state[3][3][20];
bool check(int x, int msk)
{
	for(int i = 0; i < 3; ++i)
	{
		int cL = 0, cR = 0;
		for(int j = 0; state[i][0][j]; ++j)
			if(state[i][0][j] == 'A' + x)
				cL += msk ? 1 : -1;
		for(int j = 0; state[i][1][j]; ++j)
			if(state[i][1][j] == 'A' + x)
				cR += msk ? 1 : -1;
		if(state[i][2][0] == 'u' && cL <= cR
		|| state[i][2][0] == 'e' && cL != cR
		|| state[i][2][0] == 'd' && cL >= cR)
			return 0;
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				scanf("%s", state[i][j]);
		flag = 0;
		for(int i = 0; i < 12; ++i)
			for(int j = 0; j < 2; ++j)
				if(check(i, j))
				{
					++flag;
					ans = i << 1 | j;
				}
		if(flag != 1)
			puts("cannot judge.");
		else
			printf("%c is %s.\n", 'A' + (ans >> 1), ans & 1 ? "heavy" : "light");
	}
	return 0;
}
