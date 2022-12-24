#include <cstdio>
#include <cstring>
const int maxn = 1001;
int cnt[256], mx;
char str[maxn];
int main()
{
	while(scanf("%s", str) == 1)
	{
		mx = 0;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; str[i]; ++i)
			if(mx < ++cnt[str[i]])
				mx = cnt[str[i]];
		for(int i = mx; i > 0; --i)
		{
			for(int j = 'a'; j <= 'z'; ++j)
				if(cnt[j])
					printf(" %c ", cnt[j] >= i ? '#' : ' ');
			for(int j = 'A'; j <= 'Z'; ++j)
				if(cnt[j])
					printf(" %c ", cnt[j] >= i ? '#' : ' ');
			putchar('\n');
		}
		for(int j = 'a'; j <= 'z'; ++j)
			if(cnt[j])
				printf("[%c]", j);
		for(int j = 'A'; j <= 'Z'; ++j)
			if(cnt[j])
				printf("[%c]", j);
		putchar('\n');
		putchar('\n');
	}
	return 0;
}
