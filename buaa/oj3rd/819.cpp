#include <cstdio>
int t, n, m, x, y, k, flag;
char op[2];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		x = y = flag = 0;
		while(m--)
		{
			scanf("%s%d", op, &k);
			switch(op[0])
			{
				case 'U' : x -= k; break;
				case 'D' : x += k; break;
				case 'L' : y -= k; break;
				case 'R' : y += k;
			}
			if(!(x >= 0 && x < n && y >= 0 && y < n))
				flag = 1;
		}
		if(!flag)
			printf("%d\n", y * n + x + 1);
		else
			puts("WanQuanGaoBuDong!");
	}
	return 0;
}
