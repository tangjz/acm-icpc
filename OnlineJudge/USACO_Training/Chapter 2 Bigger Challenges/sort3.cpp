/*
ID: tangjin2
LANG: C++
TASK: sort3
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, a[1000], b[1000], num[4][4], ans;
int main()
{
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b, b + n);
	for(i = 0; i < n; ++i) ++num[b[i]][a[i]];
	i = min(num[1][2], num[2][1]);
	num[1][2] -= i;
	num[2][1] -= i;
	ans += i;
	i = min(num[1][3], num[3][1]);
	num[1][3] -= i;
	num[3][1] -= i;
	ans += i;
	i = min(num[2][3], num[3][2]);
	num[2][3] -= i;
	num[3][2] -= i;
	ans += i;
	ans += max(num[1][2], num[2][1]) << 1;
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
