#include <cstdio>
int t;
long long a[3];
char str[10];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 3; ++i)
		{
			scanf("%s", str);
			int pos;
			for(pos = 0; str[pos] && str[pos] != '.'; ++pos);
			char ch = str[pos];
			str[pos] = '\0';
			if(pos)
			{
				sscanf(str, "%lld", a + i);
				a[i] *= 100000;
			}
			if(ch == '.')
			{
				++pos;
				for(int delta = 10000; delta > 0 && str[pos]; ++pos, delta /= 10)
					a[i] += (str[pos] - '0') * delta;
			}
		}
		puts(100000 * (a[0] * a[1] + a[1] * a[2] + a[2] * a[0]) < a[0] * a[1] * a[2] ? "YES" : "NO");
	}
	return 0;
}
