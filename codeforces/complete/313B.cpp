#include <cstdio>
#include <cstring>
int n, m, sum[100001] = {};
char ch[100001];
int main()
{
	int i, l, r;
	scanf("%s%d", ch, &m);
	n = strlen(ch);
	for(i = 1; i < n; ++i)
	{
		sum[i] += sum[i - 1];
		if(ch[i] == ch[i - 1]) ++sum[i];
	}
	while(m--)
	{
		scanf("%d%d", &l, &r);
		printf("%d\n", sum[r - 1] - sum[l - 1]);
	}
	return 0;
}
