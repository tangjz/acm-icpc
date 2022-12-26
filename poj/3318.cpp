#include <ctime>
#include <cstdio>
#include <cstdlib>
const int maxn = 501, maxk = 20;
int n;
struct Matrix
{
	int r, c, num[maxn][maxn];
	bool operator == (const Matrix &x) const
	{
		if(r != x.r || c != x.c)
			return 0;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				if(num[i][j] != x.num[i][j])
					return 0;
		return 1;
	}
	Matrix operator * (const Matrix &x) const
	{
		Matrix tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.num[i][k] += num[i][j] * x.num[j][k];
		return tmp;
	}
} A, B, C, D, E, F;
int main()
{
	srand(time(0));
	scanf("%d", &n);
	A.r = A.c = B.r = B.c = C.r = C.c = D.c = n;
	D.r = 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", &A.num[i][j]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", &B.num[i][j]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", &C.num[i][j]);
	bool flag = 1;
	for(int i = 0; i < maxk; ++i)
	{
		for(int j = 0; j < n; ++j)
			D.num[0][j] = rand() % 100;
		E = D * A * B;
		F = D * C;
		if(!(E == F))
		{
			flag = 0;
			break;
		}
	}
	puts(flag ? "YES" : "NO");
	return 0;
}
