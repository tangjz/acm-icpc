#include <cstdio>
#include <algorithm>
using namespace std;
int cnt[2][26];
char str[101];
int main()
{
	for(int i = 0; i < 2; ++i)
	{
		scanf("%s", str);
		for(int it = 0; str[it]; ++it)
			++cnt[i][(int)(str[it] - 'A')];
		sort(cnt[i], cnt[i] + 26);
	}
	for(int i = 0; i < 26; ++i)
		if(cnt[0][i] != cnt[1][i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
