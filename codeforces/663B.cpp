#include <cstdio>
#include <cstring>
int n, sta[10], pw10[10], s[10], num;
char str[100];
int main()
{
	pw10[0] = 1;
	for(int i = 1, j = 1989; i < 10; ++i)
	{
		pw10[i] = pw10[i - 1] * 10;
		s[i] = s[i - 1] + pw10[i];
		sta[i] = j % pw10[i];
		j += pw10[i];
	}
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", str);
		int len = strlen(str + 4);
		sscanf(str + 4, "%d", &num);
		if(num < sta[len])
			num = num - sta[len] + pw10[len] + s[len - 1];
		else
			num = num - sta[len] + s[len - 1];
		printf("%d\n", num + 1989);
	}
	return 0;
}
