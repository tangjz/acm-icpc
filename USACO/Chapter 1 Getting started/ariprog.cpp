/*
ID: tangjin2
LANG: C++
TASK: ariprog
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, maxval, len, num[125001];
bool used[125001], flag;
int main()
{
	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);
	int i, j, b, tmp;
	scanf("%d%d", &n, &m);
	maxval = m * m << 1;
	for(i = 0; i <= m ; ++i)
		for(j = i; j <= m; ++j)
		{
			tmp = i * i + j * j;
			if(used[tmp]) continue;
			used[tmp] = 1;
			num[len++] = tmp;
		}
	sort(num, num + len);
	for(b = 1; b <= num[len - 1] / (n - 1); ++b)
		for(i = 0; num[i] + (n - 1) * b <= maxval; ++i)
		{
			for(j = 0; j < n; ++j) if(!used[num[i] + j * b]) break;
			if(j < n) continue;
			printf("%d %d\n", num[i], b);
			flag = 1;
		}
	if(!flag) puts("NONE");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
