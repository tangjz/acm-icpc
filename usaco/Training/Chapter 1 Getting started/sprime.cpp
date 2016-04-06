/*
ID: tangjin2
LANG: C++
TASK: sprime
*/
#include <cmath>
#include <cstdio>
int N, n = 1;
bool prime(int x)
{
	if(x < 2) return 0;
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i) if(x % i == 0) return 0;
	return 1;
}
void dfs(int x)
{
	if(x >= n)
	{
		printf("%d\n", x);
		return;
	}
	for(int i = 1; i <= 9; ++i) if(prime(x * 10 + i)) dfs(x * 10 + i);
}
int main()
{
	freopen("sprime.in", "r", stdin);
	freopen("sprime.out", "w", stdout);
	scanf("%d", &N);
	while(N-- != 1) n *= 10;
	dfs(0);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
