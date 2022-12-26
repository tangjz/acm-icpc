#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2550, mod = 10000, maxd = 33220;
char ch[10050];
struct Big_int
{
	int len, num[maxn];
	void getstring(void)
	{
 		len = 1;
		scanf("%s", ch);
		for(int i = 0, k = strlen(ch); ; ++i)
		{
			if(i << 2 >= k) { len = i; return; }
			int sum = 0;
			for(int j = min(4, k - (i << 2)); j > 0; --j) sum = (sum << 3) + (sum << 1) + (ch[k - (i << 2) - j] - '0');
			num[i] = sum;
		}
	}
	Big_int operator / (int x) const
	{
		//if(!x) { puts("divide zero"); return *this; }
		Big_int tmp = *this;
		for(int i = len - 1; i > 0; --i)
		{
			tmp.num[i - 1] += (tmp.num[i] % x) * mod;
			tmp.num[i] /= x;
		}
		//if((tmp.num[0] % x) << 1 >= x) tmp.num[0] += x;
		tmp.num[0] /= x;
		while(tmp.len > 1 && !tmp.num[tmp.len - 1]) --tmp.len;
		return tmp;
	}
	Big_int operator /= (const int &x) { return *this = *this / x; }
	int operator % (const int &x) const
	{
		int ans = 0;
		for(int i = len - 1; i >= 0; --i) ans = ((long long)ans * mod + num[i]) % x;
		return (int)ans;
	}
};
int n, d, res[maxd], f[maxd][2];
Big_int A;
int main()
{
	A.getstring();
	scanf("%d", &n);
	if(n == 1)
	{
		puts(ch);
		return 0;
	}
	while(!(A.len == 1 && !A.num[0]))
	{
		res[++d] = A % n;
		A /= n;
	}
	for(int i = 1, j = d; i <= j; ++i, --j)
		swap(res[i], res[j]);
	f[1][0] = res[1];
	f[1][1] = n - res[1];
	for(int i = 2; i <= d; ++i)
	{
		f[i][0] = min(f[i - 1][0], f[i - 1][1] + 1) + res[i];
		f[i][1] = min(f[i - 1][0], f[i - 1][1] - 1) + n - res[i];
	}
	printf("%d\n", min(f[d][0], f[d][1] + 1));
	return 0;
}
