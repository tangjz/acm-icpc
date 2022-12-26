#include <cstdio>
int a = 1, b = 1;
char ch[7];
int main()
{
	gets(ch);
	for(int i = 0; ch[i]; ++i) a *= ch[i] - 'A' + 1; a %= 47;
	gets(ch);
	for(int i = 0; ch[i]; ++i) b *= ch[i] - 'A' + 1; b %= 47;
	puts(a ^ b ? "STAY" : "GO");
}
