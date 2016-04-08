/*
 * 设前面串的长度是len，当前点为o的概率为pi
 * 有pi的概率，len = len + 1，对答案的新增贡献为 (len + 1) ^ 2 - len ^ 2 = 2 * len + 1
 * 有(1 - pi)的概率，len = 0，对答案的新增贡献为 0
 */
#include <cstdio>
const int maxlen = 300001;
int n;
char s[maxlen];
double pi, len, ans;
int main()
{
	scanf("%d%s", &n, s);
	for(int i = 0; i < n; ++i)
	{
		pi = s[i] == 'x' ? 0.0 : (s[i] == 'o' ? 1.0 : 0.5);
		ans += len * pi * 2 + pi;
		len = len * pi + pi;
	}
	printf("%.4lf\n", ans);
	return 0;
}
