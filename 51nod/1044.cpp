#include <cstdio>
const int mod = 100000, maxn = 10, maxs = 20;
int cnt[mod], s1[maxn], s2[maxn], f[maxs];
int lucky(int x)
{
	return cnt[x / mod] + cnt[x % mod];
}
int find(int x)
{
	int c1, c2;
	switch(x % 10)
	{
		case 0 : case 1 : case 2 : case 5 : case 8 :
			return x + 1;
		case 3 : case 6 :
			return x + 2;
		case 4 :
			return x + 3;
		case 7 : case 9 :
			for(c1 = 0; x % 10 == 7; x /= 10, ++c1);
			if(x % 10 == 4)
				return (x + 3) * s2[c1] + s1[c1] * 4;
			c2 = lucky(x++);
			switch(c2 - lucky(x))
			{
				case 0 : return x * s2[c1] + s1[c1] * 4;
				case 1 : return x * s2[c1] + s1[c1 + 1] * 4;
				case -1 :
					if(c1)
						return x * s2[c1] + s1[c1 - 1] * 4;
					for( ; x % 10 == 0; x /= 10, ++c1);
					return (x + 1) * s2[c1];
			}
	}
}
int solve(int x, int y)
{
	if(y == 1)
		return find(x);
	int ret = solve(x / 10, (x + y - 1) / 10 - x / 10 + 1) * 10 + x % 10;
	if(y >= 20)
		return ret;
	for(int i = 0; i < y; ++i)
		f[i] = lucky(x + i);
	for(int cur = find(x); cur < ret; cur = find(cur))
	{
		bool flag = 1;
		for(int i = 0; i < y && flag; ++i)
			flag &= f[i] == lucky(cur + i);
		if(flag)
			return cur;
	}
	return ret;
}
int main()
{
	int x, y;
	for(int i = 1; i < mod; ++i)
		cnt[i] = cnt[i / 10] + (i % 10 == 4 || i % 10 == 7);
	s2[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		s1[i] = s1[i - 1] * 10 + 1;
		s2[i] = s2[i - 1] * 10;
	}
	scanf("%d%d", &x, &y);
	printf("%d\n", solve(x, y));
	return 0;
}
