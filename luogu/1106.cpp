#include <cstdio>
#include <cstring>
int s;
char ch[256];
int main()
{
	scanf("%s%d", ch, &s);
	int i, j, length = strlen(ch);
	while(s--)
	{
		for(i = 0; i < length; ++i) if(ch[i] > ch[i + 1]) { j = i; break; }
		for( ; j < length; ++j) ch[j] = ch[j + 1];
		--length;
	}
	while(ch[0] == '0')
	{
		for(i = 0; i < length; ++i) ch[i] = ch[i + 1];
		--length;
	}
	if(ch[0] == '\0') printf("0\n");
	else printf("%s\n", ch);
	return 0;
}