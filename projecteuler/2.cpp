#include <cstdio>
const int lim = 4000000;
int f[100], sum = 10;
int main()
{
	int i;
	f[1] = 2, f[2] = 8;
	for(i = 3; ; ++i)
	{
		f[i] = 4 * f[i - 1] + f[i - 2];
		if(f[i] < lim) sum += f[i];
		else break;
	}
	printf("%d\n", sum);
	return 0;
}
