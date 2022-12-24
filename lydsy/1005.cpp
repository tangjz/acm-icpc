/*
 * 设∑度 = sum，由prufer编码可知若sum > n - 2无解
 * 否则设m为未知度数点，ans = C(n - 2, num) / ∏degree[i] * m ^ (n - 2 - num)
 */
#include <cstdio>
const int mod = 10000;
struct Big_int
{
	int len, num[3000];
	Big_int operator *(const int &x) const
	{
		Big_int tmp = *this;
		for(int i = 0; i < len; ++i) tmp.num[i] *= x;
		for(int i = 0; i < len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		if(tmp.num[tmp.len]) ++tmp.len;
		return tmp;
	}
	Big_int operator *= (const int &x) { return *this = *this * x; }
	Big_int operator / (const int &x) const
	{
		Big_int tmp = *this;
		for(int i = len - 1; i; --i)
		{
			tmp.num[i - 1] += (tmp.num[i] % x) * mod;
			tmp.num[i] /= x;
		}
		tmp.num[0] /= x;
		while(!tmp.num[tmp.len - 1] && tmp.len > 1) --tmp.len;
		return tmp;
	}
	Big_int operator /= (const int &x) { return *this = *this / x; }
	void Print() const
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%4.4d", num[i]);
		printf("\n");
	}
} ans = {};
int n, m, degree[1001], sum = 0;
int main()
{
	int i, j;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i)
	{
		scanf("%d", &degree[i]);
		if(degree[i] == -1) ++m;
		else sum += degree[i] - 1;
	}
	if(n - 2 < sum) { printf("0\n"); return 0; }
	ans.len = ans.num[0] = 1;
	for(i = 1; i <= n - 2 - sum; ++i) ans *= m;
	for(i = 1; i <= n - 2; ++i) ans *= i;
	for(i = n - 2; i > sum; --i) ans /= n - i - 1;
	for(i = 1; i <= n; ++i) if(degree[i] != -1)
		for(j = 1; j <= degree[i] - 1; ++j) ans /= j;
	ans.Print();
	return 0;
}
