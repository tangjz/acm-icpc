#include <cstdio>
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
int key[4];
int decode(int num)
{
	int ret, mod, rem[4];
	for(int i = 3; i >= 0; --i)
	{
		rem[i] = num % 100;
		num /= 100;
	}
	ret = rem[0], mod = key[0];
	for(int i = 1, x, y; i < 4; ++i)
	{
		int g = exgcd(mod, key[i], x, y), r = rem[i] - ret;
		int k = key[i] / g;
		int t = (r / g * (long long)x % k + k) % k;
		ret += t * mod;
		mod *= k;
		if(ret >= mod)
			ret -= mod;
	}
	return ret;
}
int t, n, tot, temp;
char str[233], tmp[10];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		bool used = 0;
		scanf("%d%d%d%d%d", &n, &key[0], &key[1], &key[2], &key[3]);
		while(n--)
		{
			scanf("%d", &temp);
			temp = decode(temp);
			for(int i = 2; i >= 0; --i)
			{
				tmp[i] = temp % 100;
				temp /= 100;
			}
			for(int i = 0; i < 3; ++i)
				if(tmp[i] <= 26)
					str[tot++] = 'A' + tmp[i] - 1;
				else
					str[tot++] = ' ';
		}
		while(tot && str[tot - 1] == ' ')
			--tot;
		if(tot)
		{
			str[tot] = '\0';
			printf("%s", str);
			tot = 0;
		}
		putchar('\n');
	}
	return 0;
}
