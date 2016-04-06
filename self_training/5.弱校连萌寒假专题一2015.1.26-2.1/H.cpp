#include <cstdio>
#include <cstring>
int slen, tlen, ans;
char s[101], t[101];
int main()
{
	while(scanf("%s%s", s, t) == 2)
	{
		slen = strlen(s);
		tlen = strlen(t);
		ans = slen + tlen;
		for(int i = 0; i < slen; ++i)
		{
			bool flag = 0;
			for(int j = 0; s[i + j] && t[j]; ++j)
				if(s[i + j] == '2' && t[j] == '2')
				{
					flag = 1;
					break;
				}
			if(!flag && i + tlen < ans)
				ans = i + tlen;
		}
		for(int i = 0; i < tlen; ++i)
		{
			bool flag = 0;
			for(int j = 0; t[i + j] && s[j]; ++j)
				if(t[i + j] == '2' && s[j] == '2')
				{
					flag = 1;
					break;
				}
			if(!flag && i + slen < ans)
				ans = i + slen;
		}
		if(ans < slen)
			ans = slen;
		if(ans < tlen)
			ans = tlen;
		printf("%d\n", ans);
	}
	return 0;
}
