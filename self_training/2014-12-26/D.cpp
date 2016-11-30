#include <cstdio>
struct Mat
{
	int r, c;
	long long num[4][4];
	Mat operator * (const Mat &x) const
	{
		Mat tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.num[i][j] += num[i][k] * x.num[k][j];
		return tmp;
	}
	Mat pow(int k)
	{
		Mat ret = {}, tmp = *this;
		ret.r = ret.c = r;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A, B, C;
int main()
{
	int t, x, y, z, p, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d%d", &x, &y, &z, &p, &n);
		A.r = 1, A.c = 4, A.num[0][0] = A.num[0][1] = A.num[0][2] = 0, A.num[0][3] = 1;
		B.r = 4, B.c = 4;
		B.num[0][1] = x, B.num[1][0] = y, B.num[1][1] = z, B.num[2][0] = p, B.num[2][2] = B.num[3][2] = B.num[3][3] = 1;
		C = A * B.pow(n);
		printf(">>%lld\n", C.num[0][0] + C.num[0][1]);
	}
	return 0;
}
