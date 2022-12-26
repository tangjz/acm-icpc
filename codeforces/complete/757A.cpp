#include <stdio.h>
const int maxw = 257, maxs = 100001;
const char* pat = "Bulbasaur";
int cnt[maxw], need[maxw], ans = -1;
char tex[maxs];
int main()
{
	for(int i = 0; pat[i]; ++i)
		++need[pat[i]];
	scanf("%s", tex);
	for(int i = 0; tex[i]; ++i)
		++cnt[tex[i]];

	for(int i = 0; i < maxw; ++i)
	{
		if(!need[i])
			continue;
		int dt = cnt[i] / need[i];
		if(ans == -1 || ans > dt)
			ans = dt;
	}
	if(ans == -1)
		ans = 0;
	printf("%d\n", ans);
	return 0;
}
