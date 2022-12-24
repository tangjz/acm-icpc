#include <cmath>
#include <cstdio>
const int maxn = 1000, mod = 100000;
struct Big_int
{
	int len, num[maxn];
	void init(const int &number) { num[0] = number; len = 1; }
	Big_int operator -= (const int &number) { num[0] -= number; return *this; }
	Big_int operator * (const Big_int &x) const
	{
		int i, j;
		long long count;
        Big_int temp = {};
		temp.len = len + x.len - 1;
		if(temp.len > maxn) temp.len = maxn;
		for(i = 0; i < len; ++i)
			for(j = 0; j < x.len; ++j)
				if(i + j < maxn)
				{
					count = (long long)num[i] * (long long)x.num[j];
					temp. num[i + j] += count % mod;
					if(i + j + 1 < maxn) temp.num[i + j + 1] += count / mod;
				}
		for(i = 0; i < temp.len; ++i)
			if(temp.num[i] >= mod)
			{
				if(i + 1 < maxn) temp.num[i + 1] += temp.num[i] / mod;
				temp.num[i] %= mod;
			}
		while(temp.len < maxn && temp.num[temp.len])
		{
			if(temp.len + 1 < maxn) temp.num[temp.len + 1] += temp.num[temp.len] / mod;
			temp.num[temp.len++] %= mod;
		}
		return temp;
	}
	Big_int operator *= (const Big_int &x) { return *this = *this * x; }
	void Print()
	{
		for(int i = 99; i >= 0; --i)
		{
			printf("%5.5d", num[i]);
			if(i % 10 == 0) printf("\n");
		}
	}
} ans, tmp;
int p;
int main()
{
	scanf("%d", &p);
	printf("%d\n", (int)(log10(2) * p) + 1);
	ans.init(1);
	tmp.init(2);
	while(p)
	{
		if(p & 1) ans *= tmp;
		tmp *= tmp;
		p >>= 1;
	}
	(ans -= 1).Print();
}