#include <cstdio>
int n, m, ans;
char s[101][101];
bool cmp[101];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	for(int i = 0; i < m; ++i)
	{
		bool flag = 0;
		for(int j = 1; j < n; ++j)
			if(!cmp[j] && s[j][i] < s[j - 1][i])
			{
				flag = 1;
				break;
			}
		if(flag)
			++ans;
		else
			for(int j = 1; j < n; ++j)
				if(s[j][i] > s[j - 1][i])
					cmp[j] = 1;
	}
	printf("%d\n", ans);
	return 0;
}
