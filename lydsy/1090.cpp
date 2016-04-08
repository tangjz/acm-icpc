/*
 * f[i][j] 表示i到j的最短折叠长度 
 * 随便dp一下就好了 - - 
 */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char word[101] = {};
int f[101][101];
int length(const int x) { return (int)log10(x) + 3; } 
int dp(const int x, const int y);
int calc(const int x, const int y)
{
	int i, j, len = y - x + 1;
	for(i = 1; i < len; ++i)
		if(len % i == 0)
		{
			for(j = i; j < len; ++j)
				if(word[j + x] != word[j % i + x]) break;
			if(j == len) return length(len / i) + dp(x, x + i - 1);
		}
	return len;
}
int dp(const int x, const int y)
{
	if(f[x][y]) return f[x][y];
	f[x][y] = calc(x, y);
	for(int i = x; i < y; ++i) f[x][y] = min(f[x][y], dp(x,i) + dp(i + 1, y));
	return f[x][y];
}
int main()
{
	scanf("%s", word);
	printf("%d\n", dp(0, strlen(word) - 1));
	return 0;
}
