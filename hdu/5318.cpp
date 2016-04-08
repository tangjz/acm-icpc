#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 55, p = 1000000007;
typedef long long LL;
int t, n, m, num[maxn], len[maxn];
char str[maxn][100];
void inc(int &x, int y)
{
	x += y;
	if(x >= p)
		x -= p;
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
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					inc(tmp.num[i][k], (LL)num[i][j] * x.num[j][k] % p);
		return tmp;
	}
} A, B;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", num + i);
		}
		sort(num, num + n);
		n = unique(num, num + n) - num;
		for(int i = 0; i < n; ++i)
		{
			sprintf(str[i], "%d", num[i]);
			len[i] = strlen(str[i]);
		}
		if(!n || !m)
		{
			puts("0");
			continue;
		}
		A.r = 1;
		A.c = n;
		for(int i = 0; i < n; ++i)
			A.num[0][i] = 1;
		B.r = B.c = n;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				B.num[i][j] = 0;
				for(int k = 2; k <= len[i] && k <= len[j]; ++k)
				{
					bool flag = 1;
					for(int o = 0; o < k && flag; ++o)
						flag &= str[i][len[i] - k + o] == str[j][o];
					if(flag)
					{
						B.num[i][j] = 1;
						break;
					}
				}
			}
		--m;
		while(m)
		{
			if(m & 1)
				A = A * B;
			B = B * B;
			m >>= 1;
		}
		int ans = 0;
		for(int i = 0; i < n; ++i)
			inc(ans, A.num[0][i]);
		printf("%d\n", ans);
	}
	return 0;
}
