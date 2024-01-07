#include <cstdio>
const int maxn = 100010;
int t, n, pL, pR;
char str[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%s", &n, str);
		pL = -1;
		for(int i = 0; i < n; ++i)
			if(str[i] == ')')
			{
				pL = i;
				break;
			}
		pR = -1;
		for(int i = n - 1; i >= 0; --i)
			if(str[i] == '(')
			{
				pR = i;
				break;
			}
		if(pL == -1 || pR == -1)
		{
			puts("No");
			continue;
		}
		str[pL] = '(';
		str[pR] = ')';
		bool flag = 1;
		int c = 0;
		for(int i = 0; i < n; ++i)
		{
			c += str[i] == '(' ? 1 : -1;
			if(c < 0)
			{
				flag = 0;
				break;
			}
		}
		if(c)
			flag = 0;
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
