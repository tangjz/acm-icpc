#include <cstdio>
#include <cstring>
int t, top;
char str[233333], sta[233333];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str);
		int len = strlen(str);
		top = -1;
		for(int i = 0; i < len; ++i)
		{
			sta[++top] = str[i];
			while(top > 0 && sta[top] != sta[top - 1] && (sta[top] - 'a' >> 1) == (sta[top - 1] - 'a' >> 1))
				top -= 2;
		}
		if(top < 0)
			puts("sad!");
		else
		{
			sta[++top] = '\0';
			puts(sta);
		}
	}
	return 0;
}
