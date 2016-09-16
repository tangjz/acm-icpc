#include <cstdio>
int t, x, r, c, ans[21][21][21];
int main()
{
	for(x = 1; x <= 20; ++x)
		for(r = 1; r <= 20; ++r)
			for(c = 1; c <= 20; ++c)
			{
				if(x >= 7 || r * c % x != 0)
					ans[x][r][c] = 1;
				else if(r < x && c < x)
					ans[x][r][c] = 1;
				else if(r >= x && c >= x)
					ans[x][r][c] = 0;
				else
				{
					t = r < c ? r : c;
					switch(x)
					{
						case 1: ans[x][r][c] = t < 1; break;
						case 2: ans[x][r][c] = t < 1; break;
						case 3: ans[x][r][c] = t < 2; break;
						case 4: ans[x][r][c] = t < 3; break;
						case 5: ans[x][r][c] = t < 3 || t == 3 && r * c <= 15; break;
						case 6: ans[x][r][c] = t < 4; break;
					}
				}
			}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &x, &r, &c);
		printf("Case #%d: %s\n", Case, ans[x][r][c] ? "RICHARD" : "GABRIEL");
	}
	return 0;
}
