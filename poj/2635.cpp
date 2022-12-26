#include <cstdio>
#include <cstring>
const int mod = 1000000, maxx = 1000001;
int len, num[20], tot, prime[maxx], l;
char str[123];
bool vis[maxx];
int main()
{
	for(int i = 2; i < maxx; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (long long)i * prime[j] < maxx; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	while(scanf("%s%d", str, &l) == 2)
	{
		int slen = strlen(str);
		len = 0;
		for(int i = slen - 1; i >= 0; i -= 6)
		{
			num[len] = 0;
			for(int j = i < 5 ? i : 5; j >= 0; --j)
				num[len] = (num[len] << 3) + (num[len] << 1) + str[i - j] - '0';
			++len;
		}
		if(len == 1 && !num[0] && !l)
			break;
		bool flag = 0;
		for(int i = 0; i < tot && prime[i] < l; ++i)
		{
			long long ret = 0;
			for(int j = len - 1; j >= 0; --j)
				ret = (ret * mod + num[j]) % prime[i];
			if(!ret)
			{
				flag = 1;
				printf("BAD %d\n", prime[i]);
				break;
			}
		}
		if(!flag)
			puts("GOOD");
	}
	return 0;
}
