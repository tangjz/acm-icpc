#include <cstdio>
const int maxn = 55;
const char *out = "RGB";
int t, ans;
char str[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int vis[3] = {};
		ans = 0;
		scanf("%s", str);
		for(int i = 0; str[i]; ++i)
		{
			for(int j = 0; j < 3; ++j)
				ans += vis[j] >= 2 ? 2 : vis[j];
			for(int j = 0; j < 3; ++j)
				if(str[i] == out[j])
					++vis[j];
		}
		printf("%d\n", ans);
	}
	return 0;
}
