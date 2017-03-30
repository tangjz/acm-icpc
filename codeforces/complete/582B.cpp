#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 110, mod = 1000000007;
int n, t, a[maxn << 1], f[maxn << 1];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < x.c; ++j)
			{
				tmp.num[i][j] = -1;
				for(int k = 0; k < c; ++k)
					if(num[i][k] != -1 && x.num[k][j] != -1)
						upd(tmp.num[i][j], num[i][k] + x.num[k][j]);
			}
		return tmp;
	}
	Matrix pow(int k) const
	{
		Matrix ret = {}, tmp = *this;
		ret.r = ret.c = r;
		for(int i = 0; i < ret.r; ++i)
			for(int j = 0; j < ret.c; ++j)
				ret.num[i][j] = i == j ? 0 : -1;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A;
int main()
{
	scanf("%d%d", &n, &t);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		a[i + n] = a[i];
	}
	if(t == 1)
	{
		int ans = 0;
		for(int i = 0; i < n; ++i)
		{
			f[i] = 1;
			for(int j = 0; j < i; ++j)
				if(a[j] <= a[i])
					upd(f[i], f[j] + 1);
			upd(ans, f[i]);
		}
		printf("%d\n", ans);
		return 0;
	}
	A.r = A.c = n;
	for(int i = 0; i < n; ++i)
	{
		f[i] = 0;
		for(int j = i + 1; j < n << 1; ++j)
		{
			f[j] = -1;
			for(int k = i; k < j; ++k)
				if(f[k] != -1 && a[k] <= a[j])
					upd(f[j], f[k] + 1);
		}
		for(int j = 0; j < n; ++j)
			A.num[i][j] = f[j + n];
	}
	int ans = 0;
	A = A.pow(t - 1);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			upd(ans, A.num[i][j]);
	printf("%d\n", ans + 1);
	return 0;
}
