/*
 * 极大串被卡掉hash很容易，注意hash值要比mod大
 * 不AC是RP问题 
 */
#include <cstdio>
#include <cstdlib>
int n, l;
char s[100001];
int main()
{
	n = 100000, l = 13;
	for(int i = 0; i < n; i++) s[i] = rand() % 26 + 'a';
	s[n] = '\0';
	printf("%d %d\n%s\n", n, l, s);
	return 0;
}
