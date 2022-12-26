/*
 * 两个n * n的矩阵进行乘法是O(n ^ 3)的
 * 但是一个1 * n的矩阵乘一个n * n的矩阵是O(n ^ 2)的
 * 考虑将题目式子改为 T * A * B = T * C
 * 随机构造几次1 * n的矩阵T，判断答案是否相等，具有一定随机性
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int maxn = 1000;
struct Matrix
{
	int r, c, data[maxn][maxn];
	bool cmp(const Matrix &x) const
	{
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				if(data[i][j] != x.data[i][j]) return 0;
		return 1;
	}
	void Multiply(const Matrix &x, const Matrix &y)
	{
		memset(data, 0, sizeof data);
		r = x.r, c = y.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < x.c; ++j)
				for(int k = 0; k < c; ++k)
					data[i][k] += x.data[i][j] * y.data[j][k];
	}
} T, A, B, C, T1, T2;
int n;
bool flag;
int main()
{
	srand(2333);
	while(scanf("%d", &n) != EOF)
	{
		T.r = 1, T.c = A.r = A.c = B.r = B.c = C.r = C.c = n;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				scanf("%d", &A.data[i][j]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				scanf("%d", &B.data[i][j]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				scanf("%d", &C.data[i][j]);
		flag = 1;
		for(int i = 0; i < 10; ++i)
		{
			for(int j = 0; j < n; ++j)
				T.data[0][j] = rand() % 2333;
			T1.Multiply(T, A);
			T2.Multiply(T, C);
			T.Multiply(T1, B);
			if(!T.cmp(T2))
			{
				flag = 0;
				break;
			}
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
