#include <cstdio>
const char* mon[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
int t, yy1, yy2, mm, dd, ans;
char str[20];
bool m_equal(char *s, const char *t)
{
	return s[0] == t[0] && s[1] == t[1] && s[2] == t[2];
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%s %d, %d", str, &dd, &yy1);
		for(int i = 1; i <= 12; ++i)
			if(m_equal(str, mon[i - 1]))
			{
				mm = i;
				break;
			}
		if(mm > 2)
			++yy1;
		scanf("%s %d, %d", str, &dd, &yy2);
		for(int i = 1; i <= 12; ++i)
			if(m_equal(str, mon[i - 1]))
			{
				mm = i;
				break;
			}
		if(mm < 2 || mm == 2 && dd < 29)
			--yy2;
		ans = yy2 / 4 - (yy1 - 1) / 4;
		ans -= yy2 / 100 - (yy1 - 1) / 100;
		ans += yy2 / 400 - (yy1 - 1) / 400;
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
