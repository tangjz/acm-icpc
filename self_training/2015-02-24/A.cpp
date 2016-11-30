#include <cstdio>
const int maxn = 5001, maxs = 10, mod = 1000000000;
struct BigInt
{
	int len, num[maxs];
	void print()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%09d", num[i]);
		putchar('\n');
	}
	BigInt operator + (const BigInt &x) const
	{
		BigInt tmp = *this;
		if(len < x.len)
			tmp.len = x.len;
		for(int i = 0; i < tmp.len; ++i)
		{
			tmp.num[i] += x.num[i];
			if(tmp.num[i] >= mod)
			{
				tmp.num[i] -= mod;
				++tmp.num[i + 1];
			}
		}
		if(tmp.num[tmp.len])
			++tmp.len;
		return tmp;
	}
	void operator += (const BigInt &x)
	{
		*this = *this + x;
	}
} f[maxn];
int n;
int main()
{
	f[0].len = f[0].num[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		for(int j = i; j < maxn; ++j)
			f[j] += f[j - i];
	}
	while(scanf("%d", &n) != EOF)
		f[n].print();
	return 0;
}
