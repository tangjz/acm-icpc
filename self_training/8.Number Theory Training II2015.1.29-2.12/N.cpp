#include <cstdio>
#include <cstring>
const int mod = 10000;
struct BigInt
{
	int len, num[2500];
	BigInt operator * (const BigInt &x) const
	{
		BigInt tmp = {};
		long long sum = 0;
		tmp.len = len + x.len - 1;
		for(int i = 0; i < tmp.len; ++i)
		{
			for(int j = 0; j < len && j <= i; ++j)
				sum += num[j] * x.num[i - j];
			tmp.num[i] = sum % mod;
			sum /= mod;
		}
		while(sum)
		{
			tmp.num[tmp.len++] = sum % mod;
			sum /= mod;
		}
		return tmp;
	}
};
int n, k, Hash[200001];
char str[101];
bool vis[101];
int main()
{
	vis[1] = 1;
	for(int i = 2; i <= 100; ++i)
		for(int j = 2; j * j <= i; ++j)
			if(i % j == 0)
			{
				vis[i] = 1;
				break;
			}
	while(scanf("%s", str) != EOF)
		if(str[1] == 'w')
		{
			scanf("%s", str);
			puts(!vis[(int)strlen(str)] ? "Yes." : "No.");
		}
		else if(str[1] == 't')
		{
			int sum = 0, len = 0, pos = 0;
			memset(Hash, 0, sizeof Hash);
			scanf("%d", &n);
			for(int i = 1, x; i <= n; ++i)
			{
				Hash[sum] = i;
				scanf("%d", &x);
				sum = (sum + x) % n;
				if(Hash[sum] && (!len || i - Hash[sum] + 1 < len))
				{
					pos = Hash[sum];
					len = i - Hash[sum] + 1;
				}
			}
			if(!len)
				puts("¿ÉÁ¯µÄÒà·×·Æ!");
			else
				for(int i = 0; i < len; ++i)
					printf("%d%c", pos + i, " \n"[i + 1 == len]);
		}
		else if(str[2] == 'a')
		{
			scanf("%d%d", &n, &k);
			int tot = 0, flag = 0;
			for(int i = 2; (long long)i * i <= n; ++i)
				if(n % i == 0)
				{
					while(n % i == 0)
					{
						++tot;
						n /= i;
					}
					if(!flag && tot >= k)
					{
						printf("%d\n", i);
						flag = 1;
					}
				}
			if(n > 1)
			{
				++tot;
				if(!flag && tot >= k)
				{
					printf("%d\n", n);
					flag = 1;
				}
			}
			if(!flag)
				puts("no");
		}
		else
		{
			scanf("%d", &n);
			BigInt x = {}, ans = {};
			x.len = 1, x.num[0] = 2;
			ans.len = 1, ans.num[0] = 1;
			while(n)
			{
				if(n & 1)
					ans = ans * x;
				x = x * x;
				n >>= 1;
			}
			printf("%d", ans.num[ans.len - 1]);
			for(int i = ans.len - 2; i >= 0; --i)
				printf("%04d", ans.num[i]);
			putchar('\n');
		}
	return 0;
}
