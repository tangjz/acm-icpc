#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20;
int n, fact, a[maxn], f[2][maxn], last, cur;
bool equiv(int *x, int *y)
{
	for(int i = 1; i <= n; ++i)
		if(x[i] != y[i])
			return 0;
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	last = fact = 1;
	for(int i = 1; i <= n; ++i)
	{
		f[cur][i] = i;
		fact *= i;
	}
	if(equiv(a, f[cur]))
	{
		puts("ERROR");
		return 0;
	}
	for(int i = 2; i <= fact; ++i)
	{
		last ^= 1;
		cur ^= 1;
		memcpy(f[cur], f[last], sizeof f[0]);
		next_permutation(f[cur] + 1, f[cur] + n + 1);
		if(equiv(a, f[cur]))
		{
			for(int j = 1; j <= n; ++j)
				printf("%d%c", f[last][j], " \n"[j == n]);
			break;
		}
	}
}
