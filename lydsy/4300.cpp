#include <stdio.h>
const int maxs = 31;
int n, x, f[maxs], tmp;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		tmp = 0;
		for(int i = 0; i < maxs; ++i)
			if((x & (1 << i)) && tmp < f[i])
				tmp = f[i];
		++tmp;
		for(int i = 0; i < maxs; ++i)
			if(x & (1 << i))
				f[i] = tmp;
	}
	tmp = 0;
	for(int i = 0; i < maxs; ++i)
		if(tmp < f[i])
			tmp = f[i];
	printf("%d\n", tmp);
	return 0;
}
