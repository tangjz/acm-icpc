#include <stdio.h>
const int maxn = 200002;
int n, m;
char str[maxn];
int main()
{
	int pos;
	scanf("%d%d%s", &n, &m, str + 1);
	str[0] = '0';
	for(pos = 0; str[pos] && str[pos] != '.'; ++pos);
	for( ; str[pos] && str[pos] < '5'; ++pos);
	for( ; str[pos] != '.' && str[pos] >= '5' && m > 0; --pos, --m)
	{
		int idx = str[pos - 1] == '.' ? pos - 2 : pos - 1;
		++str[idx];
		for(int i = idx; str[i] > '9'; --i)
		{
			str[i] -= 10;
			++str[i - 1];
		}
		str[pos] = '\0';
	}
	if(str[pos] == '.')
		str[pos] = '\0';
	puts(str[0] == '0' ? str + 1 : str);
	return 0;
}
