#include <cmath>
#include <cstdio>
const int maxn = 10001, maxs = 1000001;
int n, x[maxn], y[maxn], xsize, xop[maxs][2], ysize, yop[maxs][2];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", x + i);
	for(int i = 0; i < n; ++i)
		scanf("%d", y + i);
	for(int i = 0; i < 30 && i < n; ++i)
		for(int j = i + 1; j < n; ++j)
		{
			if(x[i] < x[j])
			{
				x[i] ^= x[j];
				xop[xsize][0] = i, xop[xsize++][1] = j;
				x[j] ^= x[i];
				xop[xsize][0] = j, xop[xsize++][1] = i;
				x[i] ^= x[j];
				xop[xsize][0] = i, xop[xsize++][1] = j;
			}
			if((x[i] ^ x[j]) < x[j])
			{
				x[j] ^= x[i];
				xop[xsize][0] = j, xop[xsize++][1] = i;
			}
		}
	for(int i = n - 1 < 29 ? n - 1 : 29; i >= 0; --i)
		for(int j = 0; j < i; ++j)
			if((x[i] ^ x[j]) < x[j])
			{
				x[j] ^= x[i];
				xop[xsize][0] = j, xop[xsize++][1] = i;
			}
	for(int i = 0; i < 30 && i < n; ++i)
		for(int j = i + 1; j < n; ++j)
		{
			if(y[i] < y[j])
			{
				y[i] ^= y[j];
				yop[ysize][0] = i, yop[ysize++][1] = j;
				y[j] ^= y[i];
				yop[ysize][0] = j, yop[ysize++][1] = i;
				y[i] ^= y[j];
				yop[ysize][0] = i, yop[ysize++][1] = j;
			}
			if((y[i] ^ y[j]) < y[j])
			{
				y[j] ^= y[i];
				yop[ysize][0] = j, yop[ysize++][1] = i;
			}
		}
	for(int i = n - 1 < 29 ? n - 1 : 29; i >= 0; --i)
		for(int j = 0; j < i; ++j)
			if((y[i] ^ y[j]) < y[j])
			{
				y[j] ^= y[i];
				yop[ysize][0] = j, yop[ysize++][1] = i;
			}
	for(int i = 0; i < 30 && i < n; ++i)
	{
		if((int)log2(x[i]) > (int)log2(y[i]))
		{
			x[i] ^= x[i];
			xop[xsize][0] = i, xop[xsize++][1] = i;
		}
		for(int j = i + 1; j < 30 && j < n; ++j)
			if((x[i] ^ x[j]) <= y[i])
			{
				x[i] ^= x[j];
				xop[xsize][0] = i, xop[xsize++][1] = j;
			}
		if(x[i] != y[i])
		{
			puts("-1");
			return 0;
		}
	}
	printf("%d\n", xsize + ysize);
	for(int i = 0; i < xsize; ++i)
		printf("%d %d\n", xop[i][0] + 1, xop[i][1] + 1);
	for(int i = ysize - 1; i >= 0; --i)
		printf("%d %d\n", yop[i][0] + 1, yop[i][1] + 1);
	return 0;
}
