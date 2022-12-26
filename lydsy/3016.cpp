/*
 * 直接算
 */
#include <cstdio>
int ans, dep;
char ch[100010];
int main()
{
	scanf("%s", ch);
	for(int i = 0; ch[i]; ++i)
	{
		ch[i] == '(' ? ++dep : --dep;
		if(dep < 0) { ++ans; dep += 2; }
	}
	ans += dep >> 1;
	printf("%d\n", ans);
	return 0;
}
