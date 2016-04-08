#include <cstdio>
#include <cstring>
const int maxs = 100010;
int tt, len, mod, row, res;
char s[maxs], t[maxs];
int main()
{
	scanf("%d\n", &tt);
	for(int Case = 1; Case <= tt; ++Case)
	{
		gets(s);
		scanf("%d\n", &mod);
		len = strlen(s);
		row = (len - 1) / mod + 1;
		res = (len - 1) % mod + 1;
		for(int i = 0; i < len; ++i)
		{
			int ri = i / mod, ci = i % mod;
			int j = ci * row + ri - (ci > res ? ci - res : 0);
			t[i] = s[j];
		}
		t[len] = '\0';
		printf("Case #%d:\n%s\n", Case, t);
	}
	return 0;
}
