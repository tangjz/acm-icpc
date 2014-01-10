/*
ID: tangjin2
LANG: C++
TASK: barn1
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int dis[201], num[201], M, S, C, ans;
int main()
{
	freopen("barn1.in", "r", stdin);
	freopen("barn1.out", "w", stdout);
	int i;
	scanf("%d%d%d", &M, &S, &C);
	for(i = 0; i < C; ++i) scanf("%d", &num[i]);
	sort(num, num + C);
	ans = num[C - 1] - num[0] + 1;
	for(i = 1; i < C; ++i) ++dis[num[i] - num[i - 1] - 1];
	for(i = S - 1, --M; M && i; --i)
		if(dis[i])
			if(M >= dis[i])
			{
				ans -= i * dis[i];
				M -= dis[i];
			}
			else
			{
				ans -= i * M;
				M = 0;
			}
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
