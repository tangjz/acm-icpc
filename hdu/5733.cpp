#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
typedef long double LD;
struct Point
{
	LL x, y, z;
	bool read()
	{
		return scanf("%I64d%I64d%I64d", &x, &y, &z) == 3;
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y, z - t.z};
	}
	Point det(const Point &t) const
	{
		return (Point){y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x};
	}
	LD mode() const
	{
		return sqrt((LD)x * x + (LD)y * y + (LD)z * z);
	}
} A, B, C, D;
int perm[4];
LL mat[4][4];
LD alpha, a, b, c, d, s;
double r, px, py, pz;
int main()
{
	while(A.read() && B.read() && C.read() && D.read())
	{
		mat[0][0] = A.x, mat[0][1] = A.y, mat[0][2] = A.z, mat[0][3] = 1;
		mat[1][0] = B.x, mat[1][1] = B.y, mat[1][2] = B.z, mat[1][3] = 1;
		mat[2][0] = C.x, mat[2][1] = C.y, mat[2][2] = C.z, mat[2][3] = 1;
		mat[3][0] = D.x, mat[3][1] = D.y, mat[3][2] = D.z, mat[3][3] = 1;
		alpha = 0;
		for(int i = 0; i < 4; ++i)
			perm[i] = i;
		do
		{
			LL tmp = 1;
			for(int i = 0; i < 4; ++i)
			{
				tmp *= mat[i][perm[i]];
				for(int j = 0; j < i; ++j)
					if(perm[j] > perm[i])
						tmp = -tmp;
			}
			alpha += tmp;
		} while(std::next_permutation(perm, perm + 4));
		if(alpha < 0)
			alpha = -alpha;
		if(alpha < 1e-8)
		{
			puts("O O O O");
			continue;
		}
		a = (C - B).det(D - B).mode();
		b = (C - A).det(D - A).mode();
		c = (B - A).det(D - A).mode();
		d = (B - A).det(C - A).mode();
		s = a + b + c + d;
		r = alpha / s;
		px = (a * A.x + b * B.x + c * C.x + d * D.x) / s;
		py = (a * A.y + b * B.y + c * C.y + d * D.y) / s;
		pz = (a * A.z + b * B.z + c * C.z + d * D.z) / s;
		printf("%.4f %.4f %.4f %.4f\n", px, py, pz, r);
	}
	return 0;
}
