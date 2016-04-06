#include <cstdio>
#include <cstring>
const int maxn = 5002;
int n, sg[maxn];
char str[maxn];
bool flag[maxn];
int SG(bool *f, int size)
{
	int ret = 0, len = 1;
	for(int i = 2; i < size; ++i)
	{
		++len;
		if(!f[i])
		{
			ret ^= sg[len];
			len = 1;
		}
	}
	ret ^= sg[++len];
	if(str[size - 1] == str[size + 1])
		flag[size] = 1;
	return ret;
}
int main()
{
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for(int i = 3; i <= n; ++i)
	{
		int cnt = 0;
		for(int j = 0; j <= i; ++j)
			flag[j] = 0;
		for(int j = 2; j < i; ++j)
		{
			int tmp = sg[j - 1] ^ sg[i - j];
			flag[tmp] = 1;
			while(flag[cnt])
				++cnt;
		}
		sg[i] = cnt;
	}
	for(int i = 0; i <= n; ++i)
		flag[i] = i > 1 && i < n && str[i - 1] == str[i + 1];
	for(int i = 2; i < n; ++i)
		if(flag[i] && SG(flag, i - 1) == SG(flag + i, n - i))
		{
			printf("First\n%d\n", i);
			return 0;
		}
	puts("Second");
	return 0;
}
