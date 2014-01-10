/*
ID: tangjin2
LANG: C++
TASK: ride
*/
#include <cstdio>
char a[7], b[7];
int main()
{
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	int cnt1 = 1, cnt2 = 1;
	scanf("%s%s", a, b);
	for(int i = 0; a[i]; ++i)
	{
		cnt1 *= a[i] - 'A' + 1;
		cnt1 %= 47;
	}
	for(int i = 0; b[i]; ++i)
	{
		cnt2 *= b[i] - 'A' + 1;
		cnt2 %= 47;
	}
	puts(cnt1 == cnt2 ? "GO" : "STAY");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
