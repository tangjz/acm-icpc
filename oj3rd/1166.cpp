#include <cstdio>
#include <cstring>
int t, cnt[26], ans;
char str[2333];
int main()
{
	scanf("%d\n", &t);
	while(t--)
	{
		ans = 0;
		memset(cnt, 0, sizeof cnt);
		fgets(str, 2333, stdin);
		for(int i = 0; str[i]; ++i)
			if('a' <= str[i] && str[i] <= 'z')
				++cnt[str[i] - 'a'];
			else if('A' <= str[i] && str[i] <= 'Z')
				++cnt[str[i] - 'A'];
		for(int i = 1; i < 26; ++i)
			if(cnt[ans] < cnt[i])
				ans = i;
		printf("%c\n", 'a' + ans);
	}
	return 0;
}
