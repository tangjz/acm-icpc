#include <cmath>
#include <cstdio>
int cnt[26] = {};
char word[1000001];
bool check(int x)
{
    if(x < 2) return false;
    for(int i = 2, j = (int)sqrt(x); i <= j; ++i) if(x % i == 0) return false;
    return true;
}
int main()
{
	int i, maxn, minn;
	scanf("%s", word);
	for(i = 0; word[i] != '\0'; ++i) ++cnt[(int)word[i] - 'a'];
	maxn = cnt[0]; minn = ~0u >> 1;
	for(i = 1; i < 26; ++i)
	{
		if(cnt[i] > maxn) maxn = cnt[i];
		if(cnt[i] && cnt[i] < minn) minn = cnt[i];
	}
	if(check(maxn - minn)) printf("Lucky Word\n%d\n", maxn - minn);
	else printf("No Answer\n0\n");
	return 0;
}
