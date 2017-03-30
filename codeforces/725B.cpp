#include <stdio.h>
const char *ord = "fedabc";
typedef long long LL;
LL n, ans;
char ch;
int main()
{
	scanf("%I64d%c", &n, &ch);
	ans = n - 1 - (((n - 1) & 3) <= 1 ? 0 : 2);
	ans += (n - 1 >> 2) * 12;
	if(((n - 1) & 3) & 1)
		ans += 6;
	for(int i = 0; ord[i]; ++i)
	{
		++ans;
		if(ord[i] == ch)
			break;
	}
	printf("%I64d\n", ans);
	return 0;
}
