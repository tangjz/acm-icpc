#include <cstdio>
const int maxl = 103;
struct BigInt
{
	int len, num[maxl];
	void read(char str[])
	{
		for(int i = 0; i < len; ++i)
			num[i] = 0;
		for(len = 0; str[len]; ++len);
		for(int i = 0; i < len; ++i)
			num[i] = str[len - 1 - i] - '0';
		while(len > 1 && !num[len - 1])
			--len;
	}
	void print()
	{
		for(int i = len - 1; i >= 0; --i)
			printf("%d", num[i]);
		putchar('\n');
	}
	BigInt operator + (const BigInt &x) const
	{
		BigInt tmp = *this;
		if(tmp.len < x.len)
			tmp.len = x.len;
		for(int i = 0; i < tmp.len; ++i)
		{
			tmp.num[i] += x.num[i];
			tmp.num[i + 1] += tmp.num[i] / 10;
			tmp.num[i] %= 10;
		}
		if(tmp.num[tmp.len])
			++tmp.len;
		return tmp;
	}
} A, B;
char str[maxl];
int main()
{
	while(scanf("%s", str) != EOF)
	{
		B.read(str);
		A = A + B;
	}
	A.print();
	return 0;
}
