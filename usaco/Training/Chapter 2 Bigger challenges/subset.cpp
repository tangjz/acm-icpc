/*
ID: tangjin2
LANG: C++
TASK: subset
*/
#include <cstdio>
int n, sum;
unsigned int f[781];
int main()
{
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	scanf("%d", &n);
	sum = n * (n + 1) >> 1;
	if(sum & 1) puts("0");
	else
	{
		f[0] = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = sum >> 1; j >= i; --j) f[j] += f[j - i];
		printf("%u\n", f[sum >> 1] >> 1);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
